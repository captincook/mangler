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

#include "sht_entry_container.hpp"
#include "util.hpp"

using namespace elf;

SHTEntryContainer::SHTEntryContainer(ELFFile *file, const std::pair<int, int> &interval, unsigned int index) :
    Container(file, true, interval), index(index)
{
    ELFIO::elfio *elfData = file->getELFIO();
    ELFIO::section *entry = elfData->sections[index];

    if (entry)
    {
        std::string section_name(entry->get_name());
        if (section_name != "")
            setName(section_name + " header");
        else
            setName("[unnamed] header");
    }
}

std::vector<Container *> &SHTEntryContainer::getInnerContainers()
{
    if (innerContainers.empty())
    {
        Container *container;
        ELFFile *efile = dynamic_cast<ELFFile *>(getFile());
        ELFIO::elfio *elfData = efile->getELFIO();
        ELFIO::section *entry = elfData->sections[index];

        int offset = elfData->get_sections_offset() + index * elfData->get_section_entry_size();

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        container->setName("sh_name: " + ("\"" + std::string(entry->get_name())) + "\"");
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        int sh_type = entry->get_type();
        std::string sh_type_string = "";

        switch(sh_type)
        {
            case SHT_NULL:
                sh_type_string = "SHT_NULL";
                break;
            case SHT_PROGBITS:
                sh_type_string = "SHT_PROGBITS";
                break;
            case SHT_SYMTAB :
                sh_type_string = "SHT_SYMTAB";
                break;
            case SHT_STRTAB:
                sh_type_string = "SHT_STRTAB";
                break;
            case SHT_RELA:
                sh_type_string = "SHT_RELA";
                break;
            case SHT_HASH:
                sh_type_string = "SHT_HASH";
                break;
            case SHT_DYNAMIC:
                sh_type_string = "SHT_DYNAMIC";
                break;
            case SHT_NOTE :
                sh_type_string = "SHT_NOTE";
                break;
            case SHT_NOBITS:
                sh_type_string = "SHT_NOBITS";
                break;
            case SHT_REL:
                sh_type_string = "SHT_REL";
                break;
            case SHT_SHLIB:
                sh_type_string = "SHT_SHLIB";
                break;
            case SHT_DYNSYM:
                sh_type_string = "SHT_DYNSYM";
                break;
            case SHT_INIT_ARRAY:
                sh_type_string = "SHT_INIT_ARRAY";
                break;
            case SHT_FINI_ARRAY:
                sh_type_string = "SHT_FINI_ARRAY";
                break;
            case SHT_PREINIT_ARRAY:
                sh_type_string = "SHT_PREINIT_ARRAY";
                break;
            case SHT_GROUP:
                sh_type_string = "SHT_GROUP";
                break;
            case SHT_SYMTAB_SHNDX:
                sh_type_string = "SHT_SYMTAB_SHNDX";
                break;
            case SHT_LOOS:
                sh_type_string = "SHT_LOOS";
                break;
            case SHT_HIOS:
                sh_type_string = "SHT_HIOS";
                break;
            case SHT_LOPROC:
                sh_type_string = "SHT_LOPROC";
                break;
            case SHT_HIPROC:
                sh_type_string = "SHT_HIPROC";
                break;
            case SHT_LOUSER:
                sh_type_string = "SHT_LOUSER";
                break;
            case SHT_HIUSER:
                sh_type_string = "SHT_HIUSER";
                break;
            default:
                sh_type_string = printHex(sh_type);
                break;
        }

        container->setName("sh_type: " + sh_type_string);
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        std::string sh_flags_string = "";
        ELFIO::Elf_Xword flags = entry->get_flags();

        if (flags & SHF_WRITE)
            sh_flags_string += "SHF_WRITE ";
        if (flags & SHF_ALLOC)
            sh_flags_string += "SHF_ALLOC ";
        if (flags & SHF_EXECINSTR)
            sh_flags_string += "SHF_EXECINSTR ";
        if (flags & SHF_MERGE)
            sh_flags_string += "SHF_MERGE ";
        if (flags & SHF_STRINGS)
            sh_flags_string += "SHF_STRINGS ";
        if (flags & SHF_INFO_LINK)
            sh_flags_string += "SHF_INFO_LINK ";
        if (flags & SHF_LINK_ORDER)
            sh_flags_string += "SHF_LINK_ORDER ";
        if (flags & SHF_OS_NONCONFORMING)
            sh_flags_string += "SHF_OS_NONCONFORMING ";
        if (flags & SHF_GROUP)
            sh_flags_string += "SHF_GROUP ";
        if (flags & SHF_TLS)
            sh_flags_string += "SHF_TLS ";
        if (flags & SHF_COMPRESSED)
            sh_flags_string += "SHF_COMPRESSED ";
        if (flags & SHF_MASKOS)
            sh_flags_string += "SHF_MASKOS ";
        if (flags & SHF_MASKPROC)
            sh_flags_string += "SHF_MASKPROC ";

        container->setName("sh_flags: " + sh_flags_string);
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Addr)));
        container->setName("sh_addr: " + printHex(entry->get_address()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Addr);

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Off)));
        container->setName("sh_offset: " + printHex(entry->get_offset()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Off);

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        container->setName("sh_size: " + std::to_string(entry->get_size()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        container->setName("sh_link: " + std::to_string(entry->get_link()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        container->setName("sh_info: " + std::to_string(entry->get_info()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        container->setName("sh_addralign: " + std::to_string(entry->get_addr_align()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        container->setName("sh_entsize: " + std::to_string(entry->get_entry_size()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);
    }

    return innerContainers;
}

SHTEntryContainer::~SHTEntryContainer()
{

}
