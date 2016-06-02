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

#ifndef MODIFY_ASMBAR_HPP_
#define MODIFY_ASMBAR_HPP_

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "asm_viewer.hpp"
#include <file_assembly.hpp>

/**
 * The Modify form at the bottom of the ASMViewer, used to replace the selected assembly
 * instruction.
 */
class ModifyASMBar : public QWidget
{
    Q_OBJECT
public:
    explicit ModifyASMBar(ASMViewer *asmViewer, QWidget *parent = 0);

signals:

public slots:
    void editInstruction();
    void changeViewerSelection(const QItemSelection &, const QItemSelection &);
private:
    QLabel *modify;
    QLineEdit *text;
    QPushButton *ok;
    ASMViewer *asmViewer;
};

#endif // MODIFY_ASMBAR_HPP_
