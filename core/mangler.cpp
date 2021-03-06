/* The MIT License (MIT)
 *
 * Copyright (c) 2016 Ștefan-Gabriel Mirea, Adrian Dobrică
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

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "executable_viewer.hpp"
#include "main_window.hpp"

#include "file_assembly.hpp"
#include "search_engine.hpp"
#include "container.hpp"
#include "code_container.hpp"
#include "file_unit.hpp"
#include "elf_file.hpp"
#include "elfio/elfio.hpp"
#include "segvcatch.h"

void handle_segv()
{
    throw std::runtime_error("SIGSEGV");
}

void handle_fpe()
{
    throw std::runtime_error("SIGFPE");
}

int main(int argc, char *argv[])
{
    segvcatch::init_segv(&handle_segv);
    segvcatch::init_fpe();

    QApplication app(argc, argv);

    MainWindow *wn = new MainWindow();
    for (int i = 1; i < argc; ++i)
        wn->open(QString(argv[i]));
    wn->show();

    return app.exec();
}
