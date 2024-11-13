/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright 2008-2013 Code Red Technologies Ltd,
 * Copyright 2013-2024 NXP
 * Generated linker script file for MKL82Z128xxx7
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v11.9.1 [Build 2170] [2024-04-19] on Oct 18, 2024, 1:29:23 PM
 */

MEMORY
{
  /* Define each memory region */
  PROGRAM_FLASH (rx) : ORIGIN = 0x0, LENGTH = 0x20000 /* 128K bytes (alias Flash) */  
  SRAM (rwx) : ORIGIN = 0x1fffa000, LENGTH = 0x18000 /* 96K bytes (alias RAM) */  
  USB_RAM (rwx) : ORIGIN = 0x40100000, LENGTH = 0x800 /* 2K bytes (alias RAM2) */  
}

  /* Define a symbol for the top of each memory region */
  __base_PROGRAM_FLASH = 0x0  ; /* PROGRAM_FLASH */  
  __base_Flash = 0x0 ; /* Flash */  
  __top_PROGRAM_FLASH = 0x0 + 0x20000 ; /* 128K bytes */  
  __top_Flash = 0x0 + 0x20000 ; /* 128K bytes */  
  __base_SRAM = 0x1fffa000  ; /* SRAM */  
  __base_RAM = 0x1fffa000 ; /* RAM */  
  __top_SRAM = 0x1fffa000 + 0x18000 ; /* 96K bytes */  
  __top_RAM = 0x1fffa000 + 0x18000 ; /* 96K bytes */  
  __base_USB_RAM = 0x40100000  ; /* USB_RAM */  
  __base_RAM2 = 0x40100000 ; /* RAM2 */  
  __top_USB_RAM = 0x40100000 + 0x800 ; /* 2K bytes */  
  __top_RAM2 = 0x40100000 + 0x800 ; /* 2K bytes */  
