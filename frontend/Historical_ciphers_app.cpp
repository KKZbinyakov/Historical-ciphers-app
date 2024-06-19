#include "mainwindow.h"

/**
 *
 * \file Historical_ciphers_app.cpp
 *
 * This file contains the main function
 *
 */

/**
 *
 * main function
 *
 * \param[in] argc
 * \param[in] argv
 *
 * \return app.exec
 *
 */
int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  MainWindow window;
  window.setMinimumSize(700, 400);
  window.show();

  return app.exec();
}
