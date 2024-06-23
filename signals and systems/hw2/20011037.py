import sys
import numpy as np
import matplotlib.pyplot as plt
from PyQt5.QtWidgets import (QApplication, QMainWindow, QWidget, QVBoxLayout,
                             QLabel, QLineEdit, QPushButton, QHBoxLayout, QComboBox)
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
class SinyalOdev(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('Mehmet Şadi Özcan - 20011037')
        self.setGeometry(100, 100, 1200, 1400)
        self.ana_widget = QWidget(self)
        self.setCentralWidget(self.ana_widget)
        ana_layout = QVBoxLayout(self.ana_widget)

        self.girdiler = []
        self.dalga_turu = []
        sinyal_layout = QVBoxLayout()

        #Kullanıcıdan alınacak üç farklı input için alan.
        for i in range(3):
            giris_satiri = QHBoxLayout()

            #Dalga türü seçimi için combobox ve etiketi
            dalga_turu_etiketi = QLabel(f'Dalga Türü {i + 1}:')
            dalga_turu_combobox = QComboBox(self)
            dalga_turu_combobox.addItems(["Sinüs", "Kosinüs"])
            self.dalga_turu.append(dalga_turu_combobox)

            giris_satiri.addWidget(dalga_turu_etiketi)
            giris_satiri.addWidget(dalga_turu_combobox)

            #Genlik girişi ve etiketi
            giris_satiri.addWidget(QLabel(f'Genlik {i + 1} (A{i + 1}):'))
            genlik_girdisi = QLineEdit(self)
            giris_satiri.addWidget(genlik_girdisi)

            #Frekans girişi ve etiketi
            giris_satiri.addWidget(QLabel(f'Frekans {i + 1} (f{i + 1}):'))
            frekans_girdisi = QLineEdit(self)
            giris_satiri.addWidget(frekans_girdisi)

            #Faz girişi ve etiketi
            giris_satiri.addWidget(QLabel(f'Faz {i + 1} (θ{i + 1}):'))
            faz_girdisi = QLineEdit(self)
            giris_satiri.addWidget(faz_girdisi)

            self.girdiler.append((genlik_girdisi, frekans_girdisi, faz_girdisi))
            sinyal_layout.addLayout(giris_satiri)

        ana_layout.addLayout(sinyal_layout)

        #Sinyali görselleştirmek için buton
        self.plot_butonu = QPushButton('Sinyali Görselleştir', self)
        self.plot_butonu.clicked.connect(self.sinyalleri_ciz)
        ana_layout.addWidget(self.plot_butonu)

        fourier_layout = QVBoxLayout()

        #a0 ve w0 girdileri
        a0_w0_satiri = QHBoxLayout()
        self.a0_girdisi = QLineEdit(self)
        self.w0_girdisi = QLineEdit(self)
        a0_w0_satiri.addWidget(QLabel('a0:'))
        a0_w0_satiri.addWidget(self.a0_girdisi)
        a0_w0_satiri.addWidget(QLabel('w0:'))
        a0_w0_satiri.addWidget(self.w0_girdisi)
        fourier_layout.addLayout(a0_w0_satiri)

        self.ak_girdileri = []
        self.bk_girdileri = []

        #ak ve bk girdileri
        for k in range(3):
            giris_satiri = QHBoxLayout()

            ak_girdisi = QLineEdit(self)
            bk_girdisi = QLineEdit(self)
            self.ak_girdileri.append(ak_girdisi)
            self.bk_girdileri.append(bk_girdisi)

            giris_satiri.addWidget(QLabel(f'a{k + 1}:'))
            giris_satiri.addWidget(ak_girdisi)
            giris_satiri.addWidget(QLabel(f'b{k + 1}:'))
            giris_satiri.addWidget(bk_girdisi)

            fourier_layout.addLayout(giris_satiri)

        ana_layout.addLayout(fourier_layout)

        self.plot_fourier_butonu = QPushButton('Fourier Serisi Sinyalini Görselleştir', self)
        self.plot_fourier_butonu.clicked.connect(self.fourier_serisini_ciz)
        ana_layout.addWidget(self.plot_fourier_butonu)

        #Grafikler için alan
        self.figure, self.ax = plt.subplots(4, 1, figsize=(14, 20))
        self.canvas = FigureCanvas(self.figure)
        ana_layout.addWidget(self.canvas)

    def sinyalleri_ciz(self):
        t = np.linspace(0, 1, 1000) #Sinyal 1 saniyelik zaman aralığında çizilecek
        birlesik_sinyal = np.zeros_like(t)

        #Çizdirmeden önce bir önceki kalan şeyleri temizle
        for eksen in self.ax:
            eksen.cla()

        #Sinyallerin çizimi
        for i, ((genlik_girdisi, frekans_girdisi, faz_girdisi), dalga_turu_combobox) in enumerate(zip(self.girdiler, self.dalga_turu)):
            A = float(genlik_girdisi.text())
            f = float(frekans_girdisi.text())
            θ = float(faz_girdisi.text())
            dalga_turu = dalga_turu_combobox.currentText()

            #Dalga türüne göre sinyalin hesaplandığı kısım
            if dalga_turu == "Sinüs":
                sinyal = A * np.sin(2 * np.pi * f * t + θ)
            else:
                sinyal = A * np.cos(2 * np.pi * f * t + θ)

            birlesik_sinyal += sinyal #Sentez sinyale ekleme

            max_deger = np.max(sinyal)
            min_deger = np.min(sinyal)

            #Sinyali çizdirme
            self.ax[i].plot(t, sinyal, label=f'{dalga_turu} {i + 1}')
            self.ax[i].set_ylim(min_deger - 0.1 * abs(min_deger), max_deger + 0.1 * abs(max_deger))
            self.ax[i].set_title(f'{dalga_turu} Sinyali #{i + 1}')
            self.ax[i].legend()
            self.ax[i].set_xlabel('Zaman (s)')
            self.ax[i].set_ylabel(f'Genlik\nMin: {min_deger:.2f}, Max: {max_deger:.2f}')

        #Sentez sinyali çizdirme
        max_deger = np.max(birlesik_sinyal)
        min_deger = np.min(birlesik_sinyal)
        self.ax[3].plot(t, birlesik_sinyal, label='Birleştirilmiş Sinyal')
        self.ax[3].set_ylim(min_deger - 0.1 * abs(min_deger), max_deger + 0.1 * abs(max_deger))
        self.ax[3].set_title('Birleştirilmiş Sinyal')
        self.ax[3].legend()
        self.ax[3].set_xlabel('Zaman (s)')
        self.ax[3].set_ylabel(f'Genlik\nMin: {min_deger:.2f}, Max: {max_deger:.2f}')

        self.figure.tight_layout(pad=2.0)
        self.canvas.draw()

    def fourier_serisini_ciz(self):
        t = np.linspace(0, 10, 1000) #10 saniyelik zaman aralığında çizilecek
        birlesik_sinyal = np.zeros_like(t)

        for eksen in self.ax:
            eksen.cla()

        try:
            a0 = float(self.a0_girdisi.text())
            w0 = float(self.w0_girdisi.text())
        except ValueError:
            return

        birlesik_sinyal += a0

        for k in range(3):
            try:
                ak = float(self.ak_girdileri[k].text())
                bk = float(self.bk_girdileri[k].text())
            except ValueError:
                return

            if k == 0:
                sinyal = ak * np.cos(w0 * t) + bk * np.sin(w0 * t)
            else:
                sinyal = ak * np.cos((k + 1) * w0 * t) + bk * np.sin((k + 1) * w0 * t)

            birlesik_sinyal += sinyal

            max_deger = np.max(sinyal)
            min_deger = np.min(sinyal)

            #Bileşenleri çizdirme
            self.ax[k].plot(t, sinyal, label=f'Fourier Bileşeni #{k + 1}')
            self.ax[k].set_ylim(min_deger - 0.1 * abs(min_deger), max_deger + 0.1 * abs(max_deger))
            self.ax[k].set_title(f'Fourier Bileşeni #{k + 1}')
            self.ax[k].legend()
            self.ax[k].set_xlabel('Zaman (s)')
            self.ax[k].set_ylabel(f'Genlik\nMin: {min_deger:.2f}, Max: {max_deger:.2f}')

        #Sentez sinyali çizdirme
        max_deger = np.max(birlesik_sinyal)
        min_deger = np.min(birlesik_sinyal)
        self.ax[3].plot(t, birlesik_sinyal, label='Fourier Serisi Birleştirilmiş Sinyali')
        self.ax[3].set_ylim(min_deger - 0.1 * abs(min_deger), max_deger + 0.1 * abs(max_deger))
        self.ax[3].set_title('Fourier Serisi Birleştirilmiş Sinyali')
        self.ax[3].legend()
        self.ax[3].set_xlabel('Zaman (s)')
        self.ax[3].set_ylabel(f'Genlik\nMin: {min_deger:.2f}, Max: {max_deger:.2f}')

        self.figure.tight_layout(pad=2.0)
        self.canvas.draw()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    gui = SinyalOdev()
    gui.show()
    sys.exit(app.exec_())