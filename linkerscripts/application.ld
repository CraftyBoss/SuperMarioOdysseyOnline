OUTPUT_FORMAT(elf64-littleaarch64)
OUTPUT_ARCH(aarch64)

PHDRS
{
  text PT_LOAD FLAGS(5);
  rodata PT_LOAD FLAGS(4);
  data PT_LOAD FLAGS(6);
  dynamic PT_DYNAMIC;
}

SECTIONS
{
  PROVIDE(__start__ = 0x0);
  . = __start__;
  __code_start__ = .;

  /* App code */
  .text : {
    HIDDEN(__text_start__ = .);
    KEEP (*(.text.crt0))
    *(.text .text.*)
    HIDDEN(__text_end__ = .);
  } :text

  /* Trampoline and stuffs */
  .plt : { *(.plt .plt.*) } :text
  __code_end__ = .;

  /* Read-only sections */
  . = ALIGN(0x1000);

  /* App name */
  .module_name : { KEEP (*(.rodata.module_name)) } :rodata

  /* Make sure everything is aligned */
  . = ALIGN(8);

  /* App rodata */
  .rodata : {
    *(.rodata .rodata.*)
  } :rodata

  /* All the symbols needed for relocation lookup */
  .hash     : { *(.hash) } :rodata
  .gnu.hash : { *(.gnu.hash) } :rodata
  .dynsym   : { *(.dynsym .dynsym.*) } :rodata
  .dynstr   : { *(.dynstr .dynstr.*) } :rodata

  __rel_dyn_start__ = .;
  .rel.dyn : { *(.rel.dyn) } :rodata
  __rel_dyn_end__ = .;

  __rela_dyn_start__ = .;
  .rela.dyn : { *(.rela.dyn) } :rodata
  __rela_dyn_end__ = .;

  __rel_plt_start__ = .;
  .rel.plt        : { *(.rel.plt) } :rodata
  __rel_plt_end__ = .;

  __rela_plt_start__ = .;
  .rela.plt       : { *(.rela.plt) } :rodata
  __rela_plt_end__ = .;

  /* All exception handling sections */
  .gcc_except_table : { *(.gcc_except_table .gcc_except_table.*) } :rodata
  .eh_frame_hdr : {
    HIDDEN(__eh_frame_hdr_start__ = .);
    *(.eh_frame_hdr)
    HIDDEN(__eh_frame_hdr_end__ = .);
  } :rodata
  .eh_frame : { KEEP (*(.eh_frame)) } :rodata

  /* Misc .rodata stuffs (build-id, ect) */
  .note.gnu.build-id : { *(.note.gnu.build-id) } :rodata

  /* Read-write sections */
  . = ALIGN(0x1000);

  /* App data */
  .data : {
    *(.data .data.*)
  } :data

  /* This section should be made read only after relocation but in practice we will not do that */
  .data.rela.ro : {
    *(.data.rela.ro.local*)
    *(.data.rela.ro .data.rela.ro.*)
  } :data

  /* This section should be made read only after relocation but in practice we will not do that */
  .data.rel.ro : {
    *(.data.rel.ro.local*)
    *(.data.rel.ro .data.rel.ro.*)
  } :data

  /* All GOT sections */
  __got_start__ = .;
  .got : { *(.got.plt) *(.igot.plt) *(.got) *(.igot) } :data
  __got_end__ = .;

  /* The dynamic section as we need it to be stored in the binary */
  .dynamic : {
    HIDDEN(__dynamic_start__ = .);
    *(.dynamic)
  } :data :dynamic

  /* Align for .init_array/.fini_array */
  . = ALIGN(8);

  .preinit_array ALIGN(8) :
  {
    PROVIDE (__preinit_array_start__ = .);
    KEEP (*(.preinit_array))
    PROVIDE (__preinit_array_end__ = .);
  } :data

  /* App init array */
  .init_array : {
    PROVIDE (__init_array_start__ = .);
    KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*)))
    KEEP (*(.init_array))
    PROVIDE (__init_array_end__ = .);
  } :data

  /* App fini array */
  .fini_array : {
    PROVIDE (__fini_array_start__ = .);
    KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.*)))
    KEEP (*(.fini_array))
    PROVIDE (__fini_array_end__ = .);
  } :data

  /* Thread Local sections */

  .tdata : {
    __tdata_align_abs__ = ABSOLUTE(.);
    __tdata_start__ = .;
    *(.tdata .tdata.*)
    __tdata_end__ = .;
  } :data

  .tbss : {
    __tbss_align_abs__ = ABSOLUTE(.);
    __tbss_start__ = .;
    *(.tbss .tbss.*)
    *(.tcommon)
    __tbss_end__ = .;
  } :data

  /* BSS section */
  . = ALIGN(0x1000);

  .bss : {
    HIDDEN(__bss_start__ = .);
    *(.bss .bss.*)
    *(COMMON)
    . = ALIGN(8);
    HIDDEN(__bss_end__ = .);
    . = ALIGN(0x1000);
  } :data

  __end__ = ABSOLUTE(.);

  HIDDEN(__argdata__ = .);

  /DISCARD/ : {
    /* No need of the interpreter */
    *(.interp)
  }
}
