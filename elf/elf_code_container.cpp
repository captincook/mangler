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

#include "elf_code_container.hpp"

using namespace elf;

ELFCodeContainer::ELFCodeContainer(ELFFile *file, const std::pair<int, int> &interval) :
    CodeContainer(file, interval)
{
    injectionPossible = false;
}

unsigned int ELFCodeContainer::addressToOffset(unsigned long long address)
{
    /* TODO */
    return address - 0x406000;
}

void ELFCodeContainer::getContent(std::vector<std::pair<unsigned long long, std::string>> &content)
{
    ELFFile *efile = dynamic_cast<ELFFile *>(getFile());
#ifdef DEBUG
    assert(efile != nullptr);
#endif
    /* TODO: populate content using ELFIO */
    efile->getELFIO();

    content.clear();

    char inst1[] = {0x41, 0x57};
    char inst2[] = {0x89, 0x85, 0x24, 0xff, 0xff, 0xff};
    char inst3[] = {0x4c, 0x29, 0xe5};
    char inst4[] = {0x53};
    char inst5[] = {0x8b, 0x85, 0x24, 0xff, 0xff, 0xff};

    content.push_back(std::make_pair(0x406637, std::string(inst1, 2)));
    content.push_back(std::make_pair(0x406639, std::string(inst2, 6)));
    content.push_back(std::make_pair(0x40663f, std::string(inst3, 3)));
    content.push_back(std::make_pair(0x406642, std::string(inst4, 1)));
    content.push_back(std::make_pair(0x406643, std::string(inst5, 6)));
}

void ELFCodeContainer::overwrite(unsigned long long address, std::string newMachineCode)
{
    ELFFile *efile = dynamic_cast<ELFFile *>(getFile());
#ifdef DEBUG
    assert(efile != nullptr);
#endif
    /* TODO: update efile->getELFIO() */
    efile->getELFIO();
}

ELFCodeContainer::~ELFCodeContainer() {}