#include "disasm.h"


static char *progname = NULL;
static char *target = "i686-pc-linux-gnu";  /* BDF default target */
static int print_insn_digraphs = 0;                /* -X */
static char *parse_insn_digraphs = NULL;           /* -P */
static int interactive = 0;                        /* -I */

int debug = 0;                                     /* -d */
#ifdef STATISTICS
int statistics = 0;                                /* -s */
#endif



//int show_asm = 0;                                  /* -a */

void usage()
{
  fprintf(stderr, "usage: %s [XPIds] [file to disassemble]\n\n", progname);
  fprintf(stderr,"        -P <digraph> use instruction digraphs to improve linear disassembly\n");
  fprintf(stderr,"        -s           statistics mode\n");
  fprintf(stderr,"        -d           debug mode (don't use)\n");
  fprintf(stderr,"        -X           create instruction digraphs (don't use)\n");
  fprintf(stderr,"        -I           interactive mode (don't use)\n");
  exit(1);
}

int buffer_read_memory (memaddr, myaddr, length, info)
     bfd_vma memaddr;
     bfd_byte *myaddr;
     unsigned int length;
     struct disassemble_info *info;
{
  unsigned int opb = info->octets_per_byte;
  unsigned int end_addr_offset = length / opb;
  unsigned int max_addr_offset = info->buffer_length / opb; 
  unsigned int octets = (memaddr - info->buffer_vma) * opb;

  if (memaddr < info->buffer_vma
      || memaddr - info->buffer_vma + end_addr_offset > max_addr_offset)
    return -1;
  memcpy (myaddr, info->buffer + octets, length);

  return 0;
}

static void display_bfd (bfd *abfd)
{

  if (!print_insn_digraphs)
    printf ("\n%s:     file format %s\n", bfd_get_filename (abfd), abfd->xvec->name);
  
  disassemble_i386_data (abfd, print_insn_digraphs, interactive); 

}

static void display_file (char *filename, char *target)
{
  bfd *file, *arfile = (bfd *) NULL;
  char **matching;

  file = bfd_openr (filename, target);

  if (file == NULL)
    {
      fprintf(stderr, "cannot open %s\n", filename);
      return;
    }

  if (! bfd_check_format_matches (file, bfd_object, &matching)) {
    fprintf(stderr, "unrecognized file format %s\n", filename);
    return;
  }
  

  if (bfd_check_format (file, bfd_archive))
    {
      bfd *last_arfile = NULL;

      for (;;)
	{
	  bfd_set_error (bfd_error_no_error);
	  
	  arfile = bfd_openr_next_archived_file (file, arfile);
	  if (arfile == NULL)
	    {
	      if (bfd_get_error () != bfd_error_no_more_archived_files) {
		fprintf(stderr, "cannot open last file\n");
	      }
	      break;
	    }

	  display_bfd (arfile);

	  if (last_arfile != NULL)
	    bfd_close (last_arfile);
	  last_arfile = arfile;
	}

      if (last_arfile != NULL)
	bfd_close (last_arfile);
    }
  else 
    display_bfd (file);

  bfd_close (file);
}



int main (int argc, char **argv)
{
  int c;

  bfd_init ();
  progname = argv[0];

  if (! bfd_set_default_target (target)) {
    fprintf(stderr, "cannot set default target\n");
    return 1;
  }

  while ((c = getopt (argc, argv, "adsIXP:"))
	 != EOF)
    {
      switch (c)
	{
	case 0:
	  break;		/* We've been given a long option.  */

	case 'a':
	  show_asm = 1;         /* turn on simple disassembly mode */
	  break;


	case 'I':
	  interactive = 1;
	  break;

	case 'X':
	  print_insn_digraphs = TRUE;
	  break;
	  
	case 'P':
	  parse_insn_digraphs = optarg;
	  break;

	case 'd':
	  debug = 1;
	  break;

	case 's':
#ifdef STATISTICS
	  statistics = 1;
#else
	  printf("statistics mode not compiled in -- please recompile with -DSTATISTICS\n");
	  exit(1);
#endif
	  break;

	default:
	  usage();
	}
    }

  
  if (parse_insn_digraphs) {
    FILE *s;
    
    if ((s = fopen(parse_insn_digraphs, "r")) == NULL) {
      perror("unable to parse instruction digraphs");
      exit(1);
    }
    
    inst_digraph_init(&digraphs);
    inst_digraph_parse(&digraphs, s);
    fclose(s);
  }

  if (optind == argc)
     display_file ("a.out", target);
  else
    for (; optind < argc;)
      display_file (argv[optind++], target);

  return 0;
}
