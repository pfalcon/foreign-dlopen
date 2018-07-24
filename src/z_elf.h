#ifndef Z_ELF_H
#define Z_ELF_H

#include <elf.h>

#if ELFCLASS == ELFCLASS64
#  define Elf_Ehdr	Elf64_Ehdr
#  define Elf_Phdr	Elf64_Phdr
#  define Elf_auxv_t	Elf64_auxv_t
#elif ELFCLASS == ELFCLASS32
#  define Elf_Ehdr	Elf32_Ehdr
#  define Elf_Phdr	Elf32_Phdr
#  define Elf_auxv_t	Elf32_auxv_t
#else
#  error "ELFCLASS is not defined"
#endif

#endif /* Z_ELF_H */

