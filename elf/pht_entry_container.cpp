/* The MIT License (MIT)
 *
 * Copyright (c) 2016 Adrian Dobrică, Ștefan-Gabriel Mirea
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "pht_entry_container.hpp"
#include "util.hpp"

using namespace elf;

PHTEntryContainer::PHTEntryContainer(ELFFile *file, const std::pair<int, int> &interval,
    unsigned int index) : Container(file, true, interval), index(index)
{
    setName(ProgramHeaderTableContainer::getSegmentTitle(file, index) + " header");
}

std::vector<Container *> &PHTEntryContainer::getInnerContainers()
{
    if (innerContainers.empty())
    {
        ELFFile *efile = dynamic_cast<ELFFile *>(getFile());
#ifdef DEBUG
        assert(efile != nullptr);
#endif
        ELFIO::elfio *interpretor = efile->getELFIO();
        ELFIO::segment *segment = interpretor->segments[index];

        int offset = interpretor->get_segments_offset() +
                     index * interpretor->get_segment_entry_size();

        Container *container = new Container(efile, false,
            std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        ELFIO::Elf_Word p_type = segment->get_type();
        bool found = false;
        for (unsigned int i = 0; p_type_strings[i].string; ++i)
            if (p_type == p_type_strings[i].value)
            {
                container->setName(std::string("p_type: ") + p_type_strings[i].string);
                found = true;
                break;
            }
        if (!found)
            container->setName("p_type: " + printHex(p_type));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);

        container = new Container(efile, false,
            std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Off)));
        container->setName("p_offset: " + printHex(segment->get_offset()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Off);

        container = new Container(efile, false,
            std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Addr)));
        container->setName("p_vaddr: " + printHex(segment->get_virtual_address()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Addr);

        container = new Container(efile, false,
            std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Addr)));
        container->setName("p_paddr: " + printHex(segment->get_physical_address()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Addr);

        container = new Container(efile, false,
            std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        container->setName("p_filesz: " + printHex(segment->get_file_size()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);

        container = new Container(efile, false,
            std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        container->setName("p_memsz: " + printHex(segment->get_memory_size()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);

        container = new Container(efile, false,
            std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        bool first = true;
        std::string name;
        ELFIO::Elf_Word p_flags = segment->get_flags();
        for (unsigned int i = 0; p_flags_strings[i].string; ++i)
            if (p_flags & p_flags_strings[i].value)
            {
                if (!first)
                    name += '+';
                name += p_flags_strings[i].string;
                first = false;
            }
        container->setName("p_flags: " + name);
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);

        container = new Container(efile, false,
            std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        container->setName("p_align: " + printHex(segment->get_align()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);
    }

    return innerContainers;
}

PHTEntryContainer::~PHTEntryContainer() {}
