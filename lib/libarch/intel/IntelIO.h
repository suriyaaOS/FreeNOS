/*
 * Copyright (C) 2015 Niek Linnenbank
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __LIBARCH_INTELIO_H
#define __LIBARCH_INTELIO_H

#include <Types.h>

/**
 * Intel I/O functions.
 */
class IO
{
  public:

    /**
     * Read a byte from a port.
     * @param port The I/O port to read from.
     * @return A byte read from the port.
     */
    static inline u8 inb(u16 port)
    {
        u8 b;
        asm volatile ("inb %%dx, %%al" : "=a" (b) : "d" (port));
        return b;
    }

    /**
     * Read a word from a port.
     * @param port The I/O port to read from.
     * @return Word read from the port.
     */
    static inline u16 inw(u16 port)
    {
        u16 w;
        asm volatile ("inw %%dx, %%ax" : "=a" (w) : "d" (port));
        return w;
    }

    /**
     * Output a byte to a port.
     * @param port Port to write to.
     * @param byte The byte to output.
     */
    static inline void outb(u16 port, u8 byte)
    {
        asm volatile ("outb %%al,%%dx"::"a" (byte),"d" (port));
    }

    /**
     * Output a word to a port.
     * @param port Port to write to.
     * @param byte The word to output.
     */
    static inline void outw(u16 port, u16 word)
    {
        asm volatile ("outw %%ax,%%dx"::"a" (word),"d" (port));
    }

    /**
     * Output a long to a I/O port.
     * @param port Target I/O port.
     * @param l The long 32-bit number to output.
     */
    static inline void outl(u16 port, u32 l)
    {
        asm volatile ("outl %%eax,%%dx"::"a" (l),"d" (port));
    }

    /**
     * read from MMIO register
     */
    static inline u32 read(Address reg)
    {
        return *(u32 *) reg;
    }

    /**
     * write to MMIO register
     */
    static inline void write(Address reg, u32 data)
    {
        *(u32 *) reg = data;
    }
};

#endif /* __LIBARCH_INTELIO_H */
