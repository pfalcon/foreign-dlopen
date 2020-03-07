#include "elf_loader.h"
#include "z_utils.h"

int main(int argc, char *argv[])
{
	init_exec_elf(argv);

	if (argc < 2)
		z_errx(1, "no input file");

	exec_elf(argv[1], argc - 1, argv + 1);
}
