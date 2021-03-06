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

#include "ARMControl.h"

ARMControl::ARMControl()
{
}

ARMControl::~ARMControl()
{
}

u32 ARMControl::read(Register reg)
{
    switch (reg)
    {
        case MainID:               return mrc(p15, 0, 0, c0,  c0);
        case SystemControl:        return mrc(p15, 0, 0, c1,  c0);
        case TranslationTable0:    return mrc(p15, 0, 0, c2,  c0);
        case TranslationTable1:    return mrc(p15, 0, 1, c2,  c0);
        case TranslationTableCtrl: return mrc(p15, 0, 2, c2,  c0);
        case DomainControl:        return mrc(p15, 0, 0, c3,  c0);
        case UserProcID:           return mrc(p15, 0, 4, c13, c0);
        default: break;
    }
    return 0;
}

void ARMControl::write(Register reg, u32 value)
{
    switch (reg)
    {
        case SystemControl:         mcr(p15, 0, 0, c1,  c0, value); break;
        case TranslationTable0:     mcr(p15, 0, 0, c2,  c0, value); break;
        case TranslationTable1:     mcr(p15, 0, 1, c2,  c0, value); break;
        case TranslationTableCtrl:  mcr(p15, 0, 2, c2,  c0, value); break;
        case DomainControl:         mcr(p15, 0, 0, c3,  c0, value); break;
        case InstructionCacheClear: mcr(p15, 0, 0, c7,  c5, value); break;
        case UserProcID:            mcr(p15, 0, 4, c13, c0, value); break;
        default: break;
    }
}

void ARMControl::set(Register reg, u32 flags)
{
    u32 val = read(reg);
    val |= flags;
    write(reg, val);
}

void ARMControl::unset(Register reg, u32 flags)
{
    u32 val = read(reg);
    val &= ~(flags);
    write(reg, val);
}

void ARMControl::set(ARMControl::SystemControlFlags flags)
{
    set(SystemControl, flags);
}

void ARMControl::unset(ARMControl::SystemControlFlags flags)
{
    unset(SystemControl, flags);
}

void ARMControl::set(ARMControl::DomainControlFlags flags)
{
    set(DomainControl, flags);
}
