#include "mainwindow.h"

std::vector<uint8_t> hexStringToVector(const std::string& hexString)
{
    std::vector<uint8_t> result;
    for (int i = 0; i<hexString.length(); i+=3) {
        std::string byteString = hexString.substr(i, 2);
        uint8_t byte = stoi(byteString, 0, 16);
        result.push_back(byte);
    }
    return result;
}

std::string vectorToHexString(std::vector<uint8_t> vector)
{
    std::ostringstream line;
    for (int i=0; i<vector.size(); i++)
    {
        line << std::uppercase << std::hex << 256+int(vector[i]);
    }
    std::string str = line.str();
    std::string result = "";
    for (int i{1}; i<str.size()-2; i+=3)
    {
        result += str.substr(i, 2) + " ";
    }
    result += str.substr(str.size()-2, 2);
    return result;
}

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout *layout = new QGridLayout();
    layout->setColumnMinimumWidth(0, 300);
    setLayout(layout);

    comboBox = new QComboBox(this);
    for (const auto &[key, value] : cipher_types)
    {
        comboBox->addItem(QString::fromStdString(key), QVariant(value.size()));
    }
    layout->addWidget(comboBox, 0, 0, 1, 1);
    connect(comboBox, &QComboBox::currentIndexChanged, this, &MainWindow::OnComboBoxChanged);

    for (int i = 0; i < comboBox->currentData().toInt(); ++i)
    {
        QPushButton *button = new QPushButton(this);
        button->setCheckable(true);
        button->setText(QString::fromStdString(cipher_types[comboBox->currentText().toStdString()][i]));
        button->hide();
        connect(button, &QPushButton::clicked, this, &MainWindow::OnCipherSelected);
        comboboxbuttons.push_back(button);
        layout->addWidget(button);
    }
    OnComboBoxChanged(comboBox->currentIndex());

// Создаем новый QLabel и устанавливаем текст
    QLabel *inputLabel = new QLabel("Input text:", this); // Добавляем QLabel в layout перед соответствующим QLineEdit
    default_labels.push_back(inputLabel);
    inputLine = new QLineEdit(this);
    default_lines.push_back(inputLine);
    layout->addWidget(inputLabel, 0, 1, 1, 1); // Добавляем QLabel в layout перед соответствующим QLineEdit
    layout->addWidget(inputLine, 1, 1, 1, 1);
    QLabel *alphabetLabel = new QLabel("Alphabet:", this);
    default_labels.push_back(alphabetLabel);
    alphabetLine = new QLineEdit(this);
    default_lines.push_back(alphabetLine);
    alphabetLine->setText("abcdefghijklmnopqrstuvwxyz");
    layout->addWidget(alphabetLabel, 2, 1, 1, 1);
    layout->addWidget(alphabetLine, 3, 1, 1, 1);

    QLabel *replacement_Label = new QLabel("Key:", this);
    affine_labels.push_back(replacement_Label);
    replacement_Line = new QLineEdit(this);
    affine_lines.push_back(replacement_Line);
    layout->addWidget(replacement_Label, 4, 1, 1, 1);
    layout->addWidget(replacement_Line, 5, 1, 1, 1);
    replacement_Line->hide();
    replacement_Label->hide();
    QLabel *alpha_1_Label = new QLabel("Alpha_1:", this);
    affine_labels.push_back(alpha_1_Label);
    alpha_1_Line = new QLineEdit(this);
    affine_lines.push_back(alpha_1_Line);
    layout->addWidget(alpha_1_Label, 4, 1, 1, 1);
    layout->addWidget(alpha_1_Line, 5, 1, 1, 1);
    alpha_1_Line->hide();
    alpha_1_Label->hide();
    QLabel *beta_1_Label = new QLabel("Beta_1:", this);
    affine_labels.push_back(beta_1_Label);
    beta_1_Line = new QLineEdit(this);
    affine_lines.push_back(beta_1_Line);
    layout->addWidget(beta_1_Label, 4, 2, 1, 1);
    layout->addWidget(beta_1_Line, 5, 2, 1, 1);
    beta_1_Line->hide();
    beta_1_Label->hide();
    QLabel *alpha_2_Label = new QLabel("Alpha_2:", this);
    affine_labels.push_back(alpha_2_Label);
    alpha_2_Line = new QLineEdit(this);
    affine_lines.push_back(alpha_2_Line);
    layout->addWidget(alpha_2_Label, 6, 1, 1, 1);
    layout->addWidget(alpha_2_Line, 7, 1, 1, 1);
    alpha_2_Line->hide();
    alpha_2_Label->hide();
    QLabel *beta_2_Label = new QLabel("Beta_2:", this);
    affine_labels.push_back(beta_2_Label);
    beta_2_Line = new QLineEdit(this);
    affine_lines.push_back(beta_2_Line);
    layout->addWidget(beta_2_Label, 6, 2, 1, 1);
    layout->addWidget(beta_2_Line, 7, 2, 1, 1);
    beta_2_Line->hide();
    beta_2_Label->hide();

    QLabel *number_Label = new QLabel("Size of key matrix:", this);
    hill_labels.push_back(number_Label);
    number_Line = new QLineEdit(this);
    layout->addWidget(number_Label, 4, 1, 1, 1);
    layout->addWidget(number_Line, 5, 1, 1, 1);
    number_Line->hide();
    number_Label->hide();
    QPushButton *ok_Button = new QPushButton(this);
    ok_Button->setText(QString::fromStdString("OK"));
    connect(ok_Button, &QPushButton::clicked, this, &MainWindow::OnSizeEntered);
    hill_buttons.push_back(ok_Button);
    layout->addWidget(ok_Button, 5, 2, 1, 1);
    ok_Button->hide();
    QLabel *matrix_1_Label = new QLabel("Key matrix_1:", this);
    hill_labels.push_back(matrix_1_Label);
    layout->addWidget(matrix_1_Label, 6, 1, 1, 1);
    matrix_1_Label->hide();
    QLabel *matrix_2_Label = new QLabel("Key matrix_2:", this);
    hill_labels.push_back(matrix_2_Label);
    layout->addWidget(matrix_2_Label, 6, 11, 1, 1);
    matrix_2_Label->hide();
    int n{10};
    for (int i{0}; i<2*n*n; i++)
    {
        cell_Line = new QLineEdit(this);
        hill_lines.push_back(cell_Line);
        layout->addWidget(cell_Line, 7+int(i/(n*2)), 1+i%(n*2), 1, 1);
        cell_Line->hide();
        //cell_Line->setText(QString::number(i));
    }
    hill_lines.push_back(number_Line);  //ОСТОРОЖНО

    QLabel *vigenere_Label = new QLabel("Key:", this);
    vigenere_labels.push_back(vigenere_Label);
    vigenere_Line = new QLineEdit(this);
    vigenere_lines.push_back(vigenere_Line);
    layout->addWidget(vigenere_Label, 4, 1, 1, 1);
    layout->addWidget(vigenere_Line, 5, 1, 1, 1);
    vigenere_Label->hide();
    vigenere_Line->hide();

    QLabel *data_Label = new QLabel("Data:", this);
    magma_labels.push_back(data_Label);
    data_Line = new QLineEdit(this);
    magma_lines.push_back(data_Line);
    layout->addWidget(data_Label, 0, 1, 1, 1);
    layout->addWidget(data_Line, 1, 1, 1, 1);
    data_Label->hide();
    data_Line->hide();
    QLabel *key_Label = new QLabel("Key:", this);
    magma_labels.push_back(key_Label);
    key_Line = new QLineEdit(this);
    magma_lines.push_back(key_Line);
    layout->addWidget(key_Label, 2, 1, 1, 1);
    layout->addWidget(key_Line, 3, 1, 1, 1);
    key_Label->hide();
    key_Line->hide();
    QLabel *synchrolink_Label = new QLabel("Synchrolink:", this);
    magma_labels.push_back(synchrolink_Label);
    synchrolink_Line = new QLineEdit(this);
    magma_lines.push_back(synchrolink_Line);
    layout->addWidget(synchrolink_Label, 4, 1, 1, 1);
    layout->addWidget(synchrolink_Line, 5, 1, 1, 1);
    synchrolink_Label->hide();
    synchrolink_Line->hide();

//    QLabel *fileLabel = new QLabel("Path to file with data:", this);
//    fileLine = new QLineEdit(this);
//    layout->addWidget(fileLabel, 4, 0, 1, 1);
//    layout->addWidget(fileLine, 5, 0, 1, 1);
//    QPushButton *fileButton = new QPushButton("OK", this);
//    connect(fileButton, &QPushButton::clicked, this, &MainWindow::OnFileButtonClicked);
//    layout->addWidget(fileButton, 6, 0, 1, 1);
    QPushButton *encryptButton = new QPushButton("Encipher", this);
    connect(encryptButton, &QPushButton::clicked, this, &MainWindow::OnEncryptButtonClicked);
    layout->addWidget(encryptButton, 7, 0, 1, 1);
    QPushButton *decryptButton = new QPushButton("Decipher", this);
    connect(decryptButton, &QPushButton::clicked, this, &MainWindow::OnDecryptButtonClicked);
    layout->addWidget(decryptButton, 8, 0, 1, 1);
    QLabel *outputLabel = new QLabel("Output text:", this);
    outputLine = new QLineEdit(this);
    outputLine->setReadOnly(true); // делаем поле вывода недоступным для записи
    layout->addWidget(outputLabel, 9, 0, 1, 1);
    layout->addWidget(outputLine, 10, 0, 1, 1);
}

void MainWindow::OnComboBoxChanged(int index)
{
    int count = comboBox->currentData().toInt();
    for (int i = 0; i < comboboxbuttons.size(); ++i)
    {
        if (i < count)
        {
            comboboxbuttons[i]->setVisible(true);
            comboboxbuttons[i]->setText(QString::fromStdString(cipher_types[comboBox->currentText().toStdString()][i]));
            comboboxbuttons[i]->setChecked(false);
        }
        else
        {
            comboboxbuttons[i]->setVisible(false);
        }
    }
    for (QLabel *otherLabel : affine_labels)
    {
        otherLabel->hide();
    }
    for (QLineEdit *otherLine : affine_lines)
    {
        otherLine->hide();
    }
    for (QLabel *otherLabel : hill_labels)
    {
        otherLabel->hide();
    }
    for (QLineEdit *otherLine : hill_lines)
    {
        otherLine->hide();
    }
    for (QPushButton *otherButton : hill_buttons)
    {
        otherButton->hide();
    }
    for (QLabel *otherLabel : vigenere_labels)
    {
        otherLabel->hide();
    }
    for (QLineEdit *otherLine : vigenere_lines)
    {
        otherLine->hide();
    }
    for (QLabel *otherLabel : magma_labels)
    {
        otherLabel->hide();
    }
    for (QLineEdit *otherLine : magma_lines)
    {
        otherLine->hide();
    }
}

void MainWindow::OnCipherSelected()
{
    outputLine->clear();
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button)
    {
        for (QPushButton *otherButton : comboboxbuttons)
        {
            if (otherButton != button)
            {
                otherButton->setChecked(false); // снимаем выбор с других кнопок
            }
        }
        lastClickedButton = button;
    }

    if (comboBox->currentText().toStdString() == "Affine ciphers")
    {
        default_lines[0]->show();
        default_lines[1]->show();
        default_labels[0]->show();
        default_labels[1]->show();
        for (QLabel *otherLabel : affine_labels)
        {
            otherLabel->hide();
        }
        for (QLineEdit *otherLine : affine_lines)
        {
            otherLine->clear();
            otherLine->hide();
        }
        if (lastClickedButton->text().toStdString() == "Simple replacement")
        {
            affine_labels[0]->show();
            affine_lines[0]->show();
            affine_lines[0]->setText("abcdefghijklmnopqrstuvwxyz");
        }
        if (lastClickedButton->text().toStdString() == "Affine")
        {
            affine_labels[1]->show();
            affine_labels[2]->show();
            affine_lines[1]->show();
            affine_lines[1]->setText("1");
            affine_lines[2]->show();
            affine_lines[2]->setText("1");
        }
        if (lastClickedButton->text().toStdString() == "Recurrent affine")
        {
            for (int i = 1; i < affine_labels.size(); ++i)
            {
                affine_labels[i]->show();
            }
            for (int i = 1; i < affine_lines.size(); ++i)
            {
                affine_lines[i]->show();
                affine_lines[i]->setText("1");
            }
        }
    }

    if (comboBox->currentText().toStdString() == "Hill ciphers")
    {
        default_lines[0]->show();
        default_lines[1]->show();
        default_labels[0]->show();
        default_labels[1]->show();
        for (QLabel *otherLabel : hill_labels)
        {
            otherLabel->hide();
        }
        for (QLineEdit *otherLine : hill_lines)
        {
            otherLine->clear();
            otherLine->hide();
        }
        for (QPushButton *otherButton : hill_buttons)
        {
            otherButton->hide();
        }
        hill_labels[0]->show();
        hill_lines[200]->show();
        hill_lines[200]->clear();
        hill_buttons[0]->show();
    }

    if (comboBox->currentText().toStdString() == "Vigenere ciphers")
    {
        default_lines[0]->show();
        default_lines[1]->show();
        default_labels[0]->show();
        default_labels[1]->show();
        for (QLabel *otherLabel : vigenere_labels)
        {
            otherLabel->hide();
        }
        for (QLineEdit *otherLine : vigenere_lines)
        {
            otherLine->clear();
            otherLine->hide();
        }
        vigenere_labels[0]->show();
        vigenere_lines[0]->show();
        vigenere_lines[0]->setText("a");
    }

    if (comboBox->currentText().toStdString() == "Magma ciphers")
    {
        default_lines[0]->hide();
        default_lines[1]->hide();
        default_labels[0]->hide();
        default_labels[1]->hide();
        for (QLabel *otherLabel : magma_labels)
        {
            otherLabel->hide();
        }
        for (QLineEdit *otherLine : magma_lines)
        {
            otherLine->clear();
            otherLine->hide();
        }
        if (lastClickedButton->text().toStdString() == "Magma cipher")
        {
            for (int i{0}; i<2; i++)
            {
                magma_labels[i]->show();
                magma_lines[i]->show();
            }
        }
        if (lastClickedButton->text().toStdString() == "Gamma")
        {
            for (int i{0}; i<3; i++)
            {
                magma_labels[i]->show();
                magma_lines[i]->show();
            }
        }
        if (lastClickedButton->text().toStdString() == "Feedback gamma")
        {
            for (int i{0}; i<3; i++)
            {
                magma_labels[i]->show();
                magma_lines[i]->show();
            }
        }
    }
}

std::vector<std::vector<int>> MainWindow::OnSizeEntered()
{
    std::vector<std::vector<int>> cells;
    int n = number_Line->text().toInt();
    if (n > 10)
    {
        throw input_data_invalid("The key matrix is too big");
        number_Line->clear();
    }
    else
    {
        if (lastClickedButton->text().toStdString() == "Hill cipher")
        {
            hill_labels[1]->show();
            for (int i{0}; i<200; i++)
            {
                hill_lines[i]->hide();
            }
            for (int i{0}; i<n; i++)
            {
                std::vector<int> stroke;
                for (int j{0}; j<n; j++)
                {
                    hill_lines[i*20+j]->show();
                    hill_lines[i*20+j]->setText("1");
                    stroke.push_back(i*20+j);
                }
                cells.push_back(stroke);
            }
        }
        if (lastClickedButton->text().toStdString() == "Recurrent Hill cipher")
        {
            hill_labels[1]->show();
            hill_labels[2]->show();
            for (int i{0}; i<200; i++)
            {
                hill_lines[i]->hide();
            }
            for (int i{0}; i<n; i++)
            {
                std::vector<int> stroke;
                for (int j{0}; j<n; j++)
                {
                    hill_lines[i*20+j]->show();
                    hill_lines[i*20+j]->setText("1");
                    stroke.push_back(i*20+j);
                    hill_lines[i*20+j+10]->show();
                    hill_lines[i*20+j+10]->setText("1");
                    stroke.push_back(i*20+j+10);
                }
                cells.push_back(stroke);
            }
        }
    }
    return cells;
}

//std::vector<std::string> MainWindow::OnFileButtonClicked()
//{
    //QString filePath = fileLine->text();
    //QFile inputFile(filePath);
//    QString filename="C:\\X\\HSE\\AlgProg\\A_PROJECT\\Files\\data.txt";
//    QFile inputFile(filename);
//    inputFile.open(QIODevice::ReadOnly);
//    if (!inputFile.isOpen()) {
//        QTextStream in(&inputFile);
//        while (!in.atEnd())
//        {
//            QString line = in.readLine();
            //std::cout << line.toStdString();
//        }
//        inputFile.close();
//    }
    //if (lastClickedButton->text().toStdString() == "Шифр простой замены")
    //{
        //std::cout << data[0];
        //inputLine->setText(data.at(0));
    //}
    //return data;
//}

void MainWindow::OnEncryptButtonClicked()
{
    QString inputText = inputLine->text();
    std::string alphabet = alphabetLine->text().toStdString();
    try
    {
        //if (inputText.isEmpty())
        //{
        //    throw input_data_invalid("Не введен текст");
        //}
        //if (!lastClickedButton)
        //{
        //    throw input_data_invalid("Не выбран тип шифра");
        //}
        //if (!alphabetLine->text().size())
        //{
        //    throw input_data_invalid("Не введен алфавит");
        //}

        if (comboBox->currentText().toStdString() == "Affine ciphers")
        {
            if (lastClickedButton->text().toStdString() == "Simple replacement")
            {
                std::string key = replacement_Line->text().toStdString();
                outputLine->setText(QString::fromStdString(simple_replacement_encryption(inputText.toStdString(), key, alphabet)));
            }
            if (lastClickedButton->text().toStdString() == "Affine")
            {

                int alpha = alpha_1_Line->text().toInt();
                int beta = beta_1_Line->text().toInt();
                std::vector<int> key{alpha, beta};
                //if (key.size() != 2)
                //{
                //    throw input_data_invalid("Ключ должен состоять из двух чисел");
                //}
                outputLine->setText(QString::fromStdString(affine_encryption(inputText.toStdString(), key, alphabet)));
            }
            if (lastClickedButton->text().toStdString() == "Recurrent affine")
            {
                int alpha_1 = alpha_1_Line->text().toInt();
                int beta_1 = beta_1_Line->text().toInt();
                int alpha_2 = alpha_2_Line->text().toInt();
                int beta_2 = beta_2_Line->text().toInt();
                std::vector<int> key{alpha_1, alpha_2, beta_1, beta_2};
                //if (key.size() != 4)
                //{
                //    throw input_data_invalid("Ключ должен состоять из четырех чисел");
                //}
                outputLine->setText(QString::fromStdString(affine_reccurent_encryption(inputText.toStdString(), key, alphabet)));
            }
        }

        if (comboBox->currentText().toStdString() == "Vigenere ciphers")
        {
            if (lastClickedButton->text().toStdString() == "Repeat key")
            {
                std::string key{vigenere_Line->text().toStdString()};
                outputLine->setText(QString::fromStdString(repeat_key_ciphering(inputText.toStdString(), key, alphabet)));
            }
            if (lastClickedButton->text().toStdString() == "Open key")
            {
                std::string key{vigenere_Line->text().toStdString()};
                outputLine->setText(QString::fromStdString(self_open_key_ciphering(inputText.toStdString(), key, alphabet)));
            }
            if (lastClickedButton->text().toStdString() == "Self cipher key")
            {
                std::string key{vigenere_Line->text().toStdString()};
                outputLine->setText(QString::fromStdString(self_cipher_key_ciphering(inputText.toStdString(), key, alphabet)));
            }
        }

        if (comboBox->currentText().toStdString() == "Hill ciphers")
        {
            if (lastClickedButton->text().toStdString() == "Hill cipher")
            {
                std::vector<std::vector<int>> cells = OnSizeEntered();
                int n = cells.size();
                std::vector<std::vector<int>> key_matrix;
                for (int i{0}; i<n; i++)
                {
                    std::vector<int> stroke;
                    for (int j{0}; j<n; j++)
                    {
                        int cell = cells[i][j];
                        stroke.push_back(hill_lines[cell]->text().toInt());
                    }
                    key_matrix.push_back(stroke);
                }
                Matrix_class Key1(key_matrix, n, n);
                outputLine->setText(QString::fromStdString(Hill_cipher_encoder(alphabet, inputText.toStdString(), Key1)));
            }
            if (lastClickedButton->text().toStdString() == "Recurrent Hill cipher")
            {
                std::vector<std::vector<int>> cells = OnSizeEntered();
                int n = cells.size();
                std::vector<std::vector<int>> key_matrix_1;
                std::vector<std::vector<int>> key_matrix_2;
                for (int i{0}; i<n; i++)
                {
                    std::vector<int> stroke_1;
                    std::vector<int> stroke_2;
                    for (int j{0}; j<2*n; j+=2)
                    {
                        int cell_1 = cells[i][j];
                        stroke_1.push_back(hill_lines[cell_1]->text().toInt());
                        int cell_2 = cells[i][j+1];
                        stroke_2.push_back(hill_lines[cell_2]->text().toInt());
                    }
                    key_matrix_1.push_back(stroke_1);
                    key_matrix_2.push_back(stroke_2);
                }
                Matrix_class Key1(key_matrix_1, n, n);
                Matrix_class Key2(key_matrix_2, n, n);
                outputLine->setText(QString::fromStdString(Rec_Hill_cipher_encoder(alphabet, inputText.toStdString(), Key1, Key2)));
            }
        }

        if (comboBox->currentText().toStdString() == "Magma ciphers")
        {
            if (lastClickedButton->text().toStdString() == "Magma cipher")
            {
                std::vector<uint8_t> data = hexStringToVector(magma_lines[0]->text().toStdString());
                std::vector<uint8_t> key = hexStringToVector(magma_lines[1]->text().toStdString());
                std::string result = vectorToHexString(magmaEncrypt(data, key));
                outputLine->setText(QString::fromStdString(result));
            }
            if (lastClickedButton->text().toStdString() == "Gamma")
            {
                std::vector<uint8_t> data = hexStringToVector(magma_lines[0]->text().toStdString());
                std::vector<uint8_t> key = hexStringToVector(magma_lines[1]->text().toStdString());
                std::vector<uint8_t> synchrolink = hexStringToVector(magma_lines[2]->text().toStdString());
                std::string result = vectorToHexString(magmaGammaEncrypt(data, key, synchrolink));
                outputLine->setText(QString::fromStdString(result));
            }
            if (lastClickedButton->text().toStdString() == "Feedback gamma")
            {
                std::vector<uint8_t> data = hexStringToVector(magma_lines[0]->text().toStdString());
                std::vector<uint8_t> key = hexStringToVector(magma_lines[1]->text().toStdString());
                std::vector<uint8_t> synchrolink = hexStringToVector(magma_lines[2]->text().toStdString());
                std::string result = vectorToHexString(magmaFeedbackGammaEncrypt(data, key, synchrolink));
                outputLine->setText(QString::fromStdString(result));
            }
        }
    }
    catch (const input_data_invalid &e)
    {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void MainWindow::OnDecryptButtonClicked()
{
    QString inputText = inputLine->text();
    std::string alphabet = alphabetLine->text().toStdString();
    try
    {
        //if (inputText.isEmpty())
        //{
        //    throw input_data_invalid("Не введен текст");
        //}
        //if (!lastClickedButton)
        //{
        //    throw input_data_invalid("Не выбран тип шифра");
        //}
        //if (!alphabetLine->text().size())
        //{
        //    throw input_data_invalid("Не введен алфавит");
        //}

        if (comboBox->currentText().toStdString() == "Affine ciphers")
        {
            if (lastClickedButton->text().toStdString() == "Simple replacement")
            {
                std::string key = replacement_Line->text().toStdString();
                outputLine->setText(QString::fromStdString(simple_replacement_decryption(inputText.toStdString(), key, alphabet)));
            }
            if (lastClickedButton->text().toStdString() == "Affine")
            {

                int alpha = alpha_1_Line->text().toInt();
                int beta = beta_1_Line->text().toInt();
                std::vector<int> key{alpha, beta};
                //if (key.size() != 2)
                //{
                //    throw input_data_invalid("Ключ должен состоять из двух чисел");
                //}
                outputLine->setText(QString::fromStdString(affine_decryption(inputText.toStdString(), key, alphabet)));
            }
            if (lastClickedButton->text().toStdString() == "Recurrent affine")
            {
                int alpha_1 = alpha_1_Line->text().toInt();
                int beta_1 = beta_1_Line->text().toInt();
                int alpha_2 = alpha_2_Line->text().toInt();
                int beta_2 = beta_2_Line->text().toInt();
                std::vector<int> key{alpha_1, alpha_2, beta_1, beta_2};
                //if (key.size() != 4)
                //{
                //    throw input_data_invalid("Ключ должен состоять из четырех чисел");
                //}
                outputLine->setText(QString::fromStdString(affine_reccurent_decryption(inputText.toStdString(), key, alphabet)));
            }
        }

        if (comboBox->currentText().toStdString() == "Vigenere ciphers")
        {
            if (lastClickedButton->text().toStdString() == "Repeat key")
            {
                std::string key{vigenere_Line->text().toStdString()};
                outputLine->setText(QString::fromStdString(repeat_key_deciphering(inputText.toStdString(), key, alphabet)));
            }
            if (lastClickedButton->text().toStdString() == "Open key")
            {
                std::string key{vigenere_Line->text().toStdString()};
                outputLine->setText(QString::fromStdString(self_open_key_deciphering(inputText.toStdString(), key, alphabet)));
            }
            if (lastClickedButton->text().toStdString() == "Self cipher key")
            {
                std::string key{vigenere_Line->text().toStdString()};
                outputLine->setText(QString::fromStdString(self_cipher_key_deciphering(inputText.toStdString(), key, alphabet)));
            }
        }

        if (comboBox->currentText().toStdString() == "Hill ciphers")
        {
            if (lastClickedButton->text().toStdString() == "Hill cipher")
            {
                std::vector<std::vector<int>> cells = OnSizeEntered();
                int n = cells.size();
                std::vector<std::vector<int>> key_matrix;
                for (int i{0}; i<n; i++)
                {
                    std::vector<int> stroke;
                    for (int j{0}; j<n; j++)
                    {
                        int cell = cells[i][j];
                        stroke.push_back(hill_lines[cell]->text().toInt());
                    }
                    key_matrix.push_back(stroke);
                }
                Matrix_class Key1(key_matrix, n, n);
                //std::string str {"1"};
                //std::cout << Hill_cipher_decoder(alphabet, inputText.toStdString(), Key1);
                outputLine->setText(QString::fromStdString(Hill_cipher_decoder(alphabet, inputText.toStdString(), Key1)));
                //outputLine->setText(QString::fromStdString(str));
            }
            if (lastClickedButton->text().toStdString() == "Recurrent Hill cipher")
            {
                std::vector<std::vector<int>> cells = OnSizeEntered();
                int n = cells.size();
                std::vector<std::vector<int>> key_matrix_1;
                std::vector<std::vector<int>> key_matrix_2;
                for (int i{0}; i<n; i++)
                {
                    std::vector<int> stroke_1;
                    std::vector<int> stroke_2;
                    for (int j{0}; j<2*n; j+=2)
                    {
                        int cell_1 = cells[i][j];
                        stroke_1.push_back(hill_lines[cell_1]->text().toInt());
                        int cell_2 = cells[i][j+1];
                        stroke_2.push_back(hill_lines[cell_2]->text().toInt());
                    }
                    key_matrix_1.push_back(stroke_1);
                    key_matrix_2.push_back(stroke_2);
                }
                Matrix_class Key1(key_matrix_1, n, n);
                Matrix_class Key2(key_matrix_2, n, n);
                outputLine->setText(QString::fromStdString(Rec_Hill_cipher_decoder(alphabet, inputText.toStdString(), Key1, Key2)));
            }
        }

        if (comboBox->currentText().toStdString() == "Magma ciphers")
        {
            if (lastClickedButton->text().toStdString() == "Magma cipher")
            {
                std::vector<uint8_t> data = hexStringToVector(magma_lines[0]->text().toStdString());
                std::vector<uint8_t> key = hexStringToVector(magma_lines[1]->text().toStdString());
                std::string result = vectorToHexString(magmaDecrypt(data, key));
                outputLine->setText(QString::fromStdString(result));
            }
            if (lastClickedButton->text().toStdString() == "Gamma")
            {
                std::vector<uint8_t> data = hexStringToVector(magma_lines[0]->text().toStdString());
                std::vector<uint8_t> key = hexStringToVector(magma_lines[1]->text().toStdString());
                std::vector<uint8_t> synchrolink = hexStringToVector(magma_lines[2]->text().toStdString());
                std::string result = vectorToHexString(magmaGammaDecrypt(data, key, synchrolink));
                outputLine->setText(QString::fromStdString(result));
            }
            if (lastClickedButton->text().toStdString() == "Feedback gamma")
            {
                std::vector<uint8_t> data = hexStringToVector(magma_lines[0]->text().toStdString());
                std::vector<uint8_t> key = hexStringToVector(magma_lines[1]->text().toStdString());
                std::vector<uint8_t> synchrolink = hexStringToVector(magma_lines[2]->text().toStdString());
                std::string result = vectorToHexString(magmaFeedbackGammaDecrypt(data, key, synchrolink));
                outputLine->setText(QString::fromStdString(result));
            }
        }
    }
    catch (const input_data_invalid &e)
    {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}
