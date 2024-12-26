/*
  Projeto: Controle de Acesso
  Autor: Rennan
  Data: 25/12/2024
  Descrição: Parte do código de controle de acesso.
  Esse codigo descreve como funciona a parte que
  le o que esta sendo escrito no teclado

  Hardwares ultilizado:
  - M5Cardputer

  Observação:
  - Acesse o site da M5Stack para baixar, instalar e configurar 
    suas placas e bibliotecas
  - Para subir o código no M5Cardputer, segure Btn G0
    antes de conectar no pc
*/


#include "M5Cardputer.h"

String data = ""; // Variável para armazenar o texto digitado.

String cadastros[][3] = { //Nome, Cadastro, Codigo RFID
  {"Rennan", "d64hhb1", "14 73 33 A3"},
  {"Ana", "libera", "12 45 78 B6"},
  {"Carlos", "aoba", "34 56 90 C8"}
};

void setup() {
    auto cfg = M5.config();
    M5Cardputer.begin(cfg, true);
    M5Cardputer.Display.setRotation(1);
    M5Cardputer.Display.setTextFont(&fonts::FreeSansBold18pt7b);
    M5Cardputer.Display.setTextSize(0.5);
    M5Cardputer.Display.fillScreen(BLACK);
    M5Cardputer.Display.setTextColor(WHITE);
    M5Cardputer.Display.drawString("Digite sua matricula", 10, 10);
    M5Cardputer.Display.drawString("e pressione Enter:", 10, 30);
}

void loop() {
    M5Cardputer.update();

    if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
        Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();

        for (auto i : status.word) {
                data += i;
        }

        if (status.del && !data.isEmpty()) {
            data.remove(data.length() - 1);
        }

        if (status.enter) {
            if (verifica_cadastro(data)) {
                M5Cardputer.Display.fillScreen(GREEN);
                M5Cardputer.Display.setTextDatum(middle_center);
                M5Cardputer.Display.drawString(data,
                                       M5Cardputer.Display.width() / 2,
                                       M5Cardputer.Display.height() / 2);
                M5Cardputer.Display.setTextDatum(top_left);
            } else {
                M5Cardputer.Display.fillScreen(RED);
                M5Cardputer.Display.setTextDatum(top_center);
                M5Cardputer.Display.drawString(data,
                                        M5Cardputer.Display.width() / 2,
                                        M5Cardputer.Display.height() / 2);
                M5Cardputer.Display.setTextDatum(top_left);
            }

            data = "";
            delay(5000);
            M5Cardputer.Display.fillScreen(BLACK);
            M5Cardputer.Display.drawString("Digite algo", 10, 10);
            M5Cardputer.Display.drawString("e pressione Enter:", 10, 30);
        } else {
            M5Cardputer.Display.fillRect(10, 115, M5Cardputer.Display.width(), 30, BLACK);
            M5Cardputer.Display.drawString(data, 10, 115);
        }
    }
}

bool verifica_cadastro(String TEXTO) {
    for (int i = 0; i < (sizeof(cadastros) / sizeof(cadastros[0])); i++) {
        if (TEXTO == cadastros[i][1]) {
            return true;
        }
    }
    return false;
}
