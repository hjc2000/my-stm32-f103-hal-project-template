/* custom.ld */
MEMORY
{
  RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 512K /* 修改为你的实际RAM大小 */
  FLASH (rx) : ORIGIN = 0x8000000, LENGTH = 512K /* 修改为你的实际Flash大小 */
}

SECTIONS
{
  .text : {
    *(.text) /* 所有.text节内容 */
  } > FLASH
  
  .data : {
    *(.data) /* 所有.data节内容 */
  } > RAM

  .bss : {
    *(COMMON)
    *(.bss) /* 所有.bss节内容 */
  } > RAM
}
