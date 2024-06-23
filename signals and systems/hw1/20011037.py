import numpy as np
import matplotlib.pyplot as plt
import pyaudio
import wave

def myConv(x,n,y,m): #Bu fonksiyonda konvolüsyon işlemi formülüne bağlı kalarak gerçeklenmiştir.
    sonuc = []
    for i in range(n+m-1):
        sum = 0
        for k in range(max(0,i-m+1),min(n,i+1)):
            sum += int(x[k]) * int(y[i - k])
        sonuc.append(sum)
    return sonuc

def compareConv(x,n,y,m): #Bu fonksiyonda, kendi yazdığımız myConv ile NumPy kütüphanesinin konvolüsyon fonksiyonu kıyaslanmış, grafiksel ve vektörel sonuçlar output olarak verilmiştir.
    x = [int(val) for val in x]
    y = [int(val) for val in y]
    nx = np.array(x, dtype=np.float64)
    ny = np.array(y, dtype=np.float64)

    numpy_Conv = np.convolve(nx, ny)
    my_Conv = myConv(x,n,y,m)

    #Grafiksel gösterim
    fig, axs = plt.subplots(4, 1, figsize=(10, 8), sharex=True)
    axs[0].stem(range(n), x, label='X[n]')
    axs[0].legend()
    axs[1].stem(range(m), y, label='Y[m]')
    axs[1].legend()
    axs[2].stem(range(n + m - 1), my_Conv, label='MyConv Sonucu')
    axs[2].legend()
    axs[3].stem(range(len(numpy_Conv)), numpy_Conv, label='Hazır Fonksiyon Sonucu')
    axs[3].legend()
    fig.suptitle('Konvolüsyon Sonuçları')
    plt.show()

    #Vektörel gösterim
    print("Vektörel gösterim:")
    print("X[n]:", x)
    print("Y[m]:", y)
    print("MyConv Sonucu:", my_Conv)
    print("Hazır Fonksiyon Sonucu:", numpy_Conv)
    return

def sistem(x, n, M, A): #Bu fonksiyonda 4.soruda verilen sistem tanımlanmıştır.
    sonuc = []
    for i in range(n):
        sum = x[i]
        for k in range(1, M + 1):
            index = max(0, min(n - 1, i - (3000 * k)))
            sum += (A ** -k) * k * x[index]
        sonuc.append(sum)
    return sonuc

def record_audio(seconds): #Bu fonksiyon ses kaydetmek için kullanılır. Frekans 8000 olarak alınmıştır.
    CHUNK = 1024
    FORMAT = pyaudio.paInt16
    CHANNELS = 1
    RATE = 8000
    RECORD_SECONDS = seconds
    WAVE_OUTPUT_FILENAME = f"recorded_{seconds}_seconds.wav"
    audio = pyaudio.PyAudio()

    stream = audio.open(format=FORMAT,
                        channels=CHANNELS,
                        rate=RATE,
                        input=True,
                        frames_per_buffer=CHUNK)
    print("Kaydediliyor...")
    frames = []
    for i in range(0, int(RATE / CHUNK * RECORD_SECONDS)):
        data = stream.read(CHUNK)
        frames.append(data)
    print("Kayıt tamamlandı.")

    stream.stop_stream()
    stream.close()
    audio.terminate()

    wf = wave.open(WAVE_OUTPUT_FILENAME, 'wb')
    wf.setnchannels(CHANNELS)
    wf.setsampwidth(audio.get_sample_size(FORMAT))
    wf.setframerate(RATE)
    wf.writeframes(b''.join(frames))
    wf.close()

    return WAVE_OUTPUT_FILENAME

def save_audio(audio_data, output_filename): #Bu fonksiyon ses dosyalarını kaydetmek için kullanılır.
    with wave.open(output_filename, 'wb') as wf:
        wf.setnchannels(1)
        wf.setsampwidth(2)
        wf.setframerate(8000)
        wf.writeframes(audio_data.tobytes())
        return

def plot_audio_signal(audio_data, sample_rate, title): #Bu fonksiyon ses verilerini grafiğe dökmek için kullanılır.
    duration = len(audio_data) / sample_rate
    time = np.linspace(0, duration, len(audio_data))

    #Grafikleme işlemi.
    plt.figure(figsize=(10, 4))
    plt.plot(time, audio_data)
    plt.title(title)
    plt.xlabel('Zaman (sn)')
    plt.ylabel('Genlik')
    plt.grid(True)
    plt.show()

if __name__ == '__main__':
    #1. ve 2. sorular
    n = int(input("Lütfen ilk dizinin uzunluğunu giriniz:"))
    m = int(input("Lütfen ikinci dizinin uzunluğunu giriniz:"))
    x = []
    y = []
    for i in range(n):
        deger = input(f"Lütfen ilk dizinin {i+1}. değerini giriniz:")
        x.append(deger)
    for i in range(m):
        deger = input(f"Lütfen ikinci dizinin {i+1}. değerini giriniz:")
        y.append(deger)

    sonuc = myConv(x,n,y,m)

    for i in sonuc:
        print(i)

    print("\n")

    compareConv(x,n,y,m)

    #3. ve 4. sorular

    #5 saniyelik ses kaydını başlatır.
    input("Kayda başlamak için bir tuşa basınız.")
    x1 = record_audio(5)
    print(f"5 saniyelik ses kaydı {x1} adlı değişkene kaydedilmiştir.")

    with wave.open(x1, 'rb') as wf:
        frames = wf.readframes(wf.getnframes())
        x1_signal = np.frombuffer(frames, dtype=np.int16)
        sample_rate = wf.getframerate()

    plot_audio_signal(x1_signal, sample_rate, title='5 Saniyelik Kaydedilen Ses')

    #Sisteme sokmak üzere impulse fonksiyonu yaratılır.
    impulse = np.zeros(8000)
    impulse[0] = 1

    M_values = [3,4,5]

    for M in M_values:
        system_response = sistem(impulse, len(impulse), M, 2) #Sistemin impulse fonksiyonuna verdiği tepkiyi kaydeder.

        with wave.open(x1, 'rb') as wf:
            frames = wf.readframes(wf.getnframes())
            x1_signal = np.frombuffer(frames, dtype=np.int16)
            sample_rate = wf.getframerate()

        #Konvolüsyon işlemlerini kendi fonksiyonumuz ve NumPy fonksiyonu ile yapar.
        convolved_audio_myConv = myConv(system_response, len(system_response), x1_signal, len(x1_signal))
        convolved_audio_numpy = np.convolve(x1_signal, system_response)

        #Sesleri WAV dosyası olarak kayıt eder.
        output_filename_myConv = f'convolved_audio5_M_{M}_myConv.wav'
        output_filename_numpy = f'convolved_audio5_M_{M}_numpy.wav'
        save_audio(np.array(convolved_audio_myConv, dtype=np.int16), output_filename_myConv)
        save_audio(np.array(convolved_audio_numpy, dtype=np.int16), output_filename_numpy)

        #Konvolüsyona uğramış sesleri yazdırır.
        plot_audio_signal(convolved_audio_myConv, sample_rate, title=f'5 Saniyelik Konvolüsyona Uğramış Ses - (M={M}) - MyConv')
        plot_audio_signal(convolved_audio_numpy, sample_rate, title=f'5 Saniyelik Konvolüsyona Uğramış Ses - (M={M}) - Numpy Konvolüsyon')

    #10 saniyelik ses kaydını başlatır.
    input("Kayda başlamak için bir tuşa basınız.")
    x2 = record_audio(10)
    print(f"10 saniyelik ses kaydı {x2} adlı değişkene kaydedilmiştir.")

    with wave.open(x2, 'rb') as wf:
        frames = wf.readframes(wf.getnframes())
        x2_signal = np.frombuffer(frames, dtype=np.int16)
        sample_rate = wf.getframerate()

    plot_audio_signal(x2_signal, sample_rate, title='10 Saniyelik Kaydedilen Ses')

    for M in M_values:
        system_response = sistem(impulse, len(impulse), M, 2) #Sistemin impulse fonksiyonuna verdiği tepkiyi kaydeder.

        with wave.open(x2, 'rb') as wf:
            frames = wf.readframes(wf.getnframes())
            x2_signal = np.frombuffer(frames, dtype=np.int16)
            sample_rate = wf.getframerate()

        #Konvolüsyon işlemlerini kendi fonksiyonumuz ve NumPy fonksiyonu ile yapar.
        convolved_audio_myConv = myConv(system_response, len(system_response), x2_signal, len(x2_signal))
        convolved_audio_numpy = np.convolve(x2_signal, system_response)

        #Sesleri WAV dosyası olarak kayıt eder.
        output_filename_myConv = f'convolved_audio10_M_{M}_myConv.wav'
        output_filename_numpy = f'convolved_audio10_M_{M}_numpy.wav'
        save_audio(np.array(convolved_audio_myConv, dtype=np.int16), output_filename_myConv)
        save_audio(np.array(convolved_audio_numpy, dtype=np.int16), output_filename_numpy)

        #Konvolüsyona uğramış sesleri yazdırır.
        plot_audio_signal(convolved_audio_myConv, sample_rate, title=f'10 Saniyelik Konvolüsyona Uğramış Ses - (M={M}) - MyConv')
        plot_audio_signal(convolved_audio_numpy, sample_rate, title=f'10 Saniyelik Konvolüsyona Uğramış Ses - (M={M}) - Numpy Konvolüsyon')

    print("Konvolüsyona sokulan tüm grafikler ekrana yazdırılmış, ses dosyaları program dizinine kaydedilmiştir.")