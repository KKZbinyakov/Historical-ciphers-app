#include "Affine_ciphers.hpp"
#include "Hill_encoder.hpp"
#include "exceptions.hpp"
#include "magma_cipher.hpp"
#include "vigenere_ciphers.hpp"
#include <QApplication>
#include <QComboBox>
#include <QFile>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTextStream>
#include <QWidget>
#include <map>
#include <string>
#include <vector>

/**
 *
 * \file mainwindow.h
 * This file contains header
 *
 */

/**
 *
 * MainWindow This class give access to all windows elements
 *
 */
class MainWindow : public QWidget {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  // ... остальные члены класса ...

private slots:
  void OnComboBoxChanged(int index);
  void OnCipherSelected();
  std::vector<std::vector<int>> OnSizeEntered(); // Для шифра Хилла
  //    std::vector<std::string> OnFileButtonClicked();
  void OnEncryptButtonClicked();
  void OnDecryptButtonClicked();

private:
  QComboBox *comboBox;
  QVector<QPushButton *> comboboxbuttons;
  QVector<QLabel *> default_labels;
  QVector<QLineEdit *> default_lines;
  QLabel *inputLabel;
  QLabel *alphabetLabel;
  QLabel *fileLabel;
  QLineEdit *inputLine;
  QLineEdit *alphabetLine;
  QLineEdit *fileLine;
  QLineEdit *outputLine;
  QPushButton *encryptButton;
  QPushButton *decryptButton;
  QPushButton *fileButton;

  QVector<QLabel *> affine_labels;
  QVector<QLineEdit *> affine_lines;
  QLabel *replacement_Label;
  QLabel *alpha_1_Label;
  QLabel *beta_1_Label;
  QLabel *alpha_2_Label;
  QLabel *beta_2_Label;
  QLineEdit *replacement_Line;
  QLineEdit *alpha_1_Line;
  QLineEdit *beta_1_Line;
  QLineEdit *alpha_2_Line;
  QLineEdit *beta_2_Line;

  QVector<QLabel *> hill_labels;
  QVector<QLineEdit *> hill_lines;
  QVector<QPushButton *> hill_buttons;
  QLabel *matrix_1_Label;
  QLabel *matrix_2_Label;
  QLabel *number_Label;
  QLineEdit *cell_Line;
  QLineEdit *number_Line;
  QPushButton *ok_Button;

  QVector<QLabel *> vigenere_labels;
  QVector<QLineEdit *> vigenere_lines;
  QLabel *vigenere_Label;
  QLineEdit *vigenere_Line;

  QVector<QLabel *> magma_labels;
  QVector<QLineEdit *> magma_lines;
  QLabel *data_Label;
  QLabel *key_Label;
  QLabel *synchrolink_Label;
  QLineEdit *data_Line;
  QLineEdit *key_Line;
  QLineEdit *synchrolink_Line;

  std::map<std::string, std::vector<std::string>> cipher_types = {
      {"Affine ciphers", {"Simple replacement", "Affine", "Recurrent affine"}},
      {"Hill ciphers", {"Hill cipher", "Recurrent Hill cipher"}},
      {"Vigenere ciphers", {"Repeat key", "Open key", "Self cipher key"}},
      {"Magma ciphers", {"Magma cipher", "Gamma", "Feedback gamma"}}};
  QPushButton *lastClickedButton = nullptr;
};

std::vector<uint8_t> hexStringToVector(const std::string &hexString);
std::string vectorToHexString(std::vector<uint8_t> vector);
