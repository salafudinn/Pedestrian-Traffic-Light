// Deklarasi Pin Lampu Kendaraan
const int pinKendaraanMerah = 10;
const int pinKendaraanKuning = 9;
const int pinKendaraanHijau = 8;

// Deklarasi Pin Lampu Pedestrian 1 & 2 (Sisi 1 dan Sisi Lainnya)
const int pinPedMerah1 = 7;
const int pinPedHijau1 = 6;

const int pinPedMerah2 = 5;
const int pinPedHijau2 = 4;

// Deklarasi 2 Pin Tombol (Gunakan pin 2 dan 3 untuk Interrupt pada Arduino Uno)
const int pinTombol1 = 2; // Tombol di sisi pejalan kaki 1
const int pinTombol2 = 3; // Tombol di sisi pejalan kaki 2

// Variabel penanda (flag) untuk ISR
volatile bool adaPenyeberang = false;

void setup() {
  // Mengatur mode pin sebagai OUTPUT
  pinMode(pinKendaraanMerah, OUTPUT);
  pinMode(pinKendaraanKuning, OUTPUT);
  pinMode(pinKendaraanHijau, OUTPUT);
  
  pinMode(pinPedMerah1, OUTPUT);
  pinMode(pinPedHijau1, OUTPUT);
  pinMode(pinPedMerah2, OUTPUT);
  pinMode(pinPedHijau2, OUTPUT);

  // Mengatur kedua pin tombol dengan resistor pull-up internal
  pinMode(pinTombol1, INPUT_PULLUP);
  pinMode(pinTombol2, INPUT_PULLUP);

  // Mengaktifkan Interrupt eksternal untuk KEDUA tombol
  // Keduanya memanggil fungsi yang sama: fungsiInterupsiTombol
  attachInterrupt(digitalPinToInterrupt(pinTombol1), fungsiInterupsiTombol, FALLING);
  attachInterrupt(digitalPinToInterrupt(pinTombol2), fungsiInterupsiTombol, FALLING);

  // Menjalankan kondisi awal saat Arduino baru dinyalakan
  setKondisiAwal();
}

void loop() {
  // Jika SALAH SATU tombol ditekan, ISR mengubah nilai adaPenyeberang menjadi true
  if (adaPenyeberang) {
    
    // 1. Saat ditekan: Kendaraan merah, pedestrian hijau
    digitalWrite(pinKendaraanHijau, LOW);
    digitalWrite(pinKendaraanMerah, HIGH);
    
    digitalWrite(pinPedMerah1, LOW);
    digitalWrite(pinPedMerah2, LOW);
    digitalWrite(pinPedHijau1, HIGH);
    digitalWrite(pinPedHijau2, HIGH);
    
    // Waktu tunggu penyeberang lewat (misal: 5 detik)
    delay(5000); 

    // 2. Setelah waktu tertentu: Pedestrian kembali merah, Kendaraan kuning
    digitalWrite(pinPedHijau1, LOW);
    digitalWrite(pinPedHijau2, LOW);
    digitalWrite(pinPedMerah1, HIGH);
    digitalWrite(pinPedMerah2, HIGH);
    
    digitalWrite(pinKendaraanMerah, LOW);
    digitalWrite(pinKendaraanKuning, HIGH);
    
    // Waktu tunggu lampu kuning (misal: 2 detik)
    delay(2000);

    // 3. Sistem kembali ke kondisi awal: Kendaraan hijau, pedestrian merah
    digitalWrite(pinKendaraanKuning, LOW);
    setKondisiAwal(); 

    // Kembalikan flag ke false agar siklus siap menerima input tombol lagi
    adaPenyeberang = false;
  }
}

// --- Fungsi Tambahan ---

// Fungsi untuk mengatur kondisi default
void setKondisiAwal() {
  digitalWrite(pinKendaraanHijau, HIGH);
  digitalWrite(pinKendaraanKuning, LOW);
  digitalWrite(pinKendaraanMerah, LOW);

  digitalWrite(pinPedMerah1, HIGH);
  digitalWrite(pinPedHijau1, LOW);
  digitalWrite(pinPedMerah2, HIGH);
  digitalWrite(pinPedHijau2, LOW);
}

// Fungsi ISR (Interrupt Service Routine)
// Tombol mana pun yang ditekan (Pin 2 atau Pin 3) akan masuk ke fungsi ini
void fungsiInterupsiTombol() {
  adaPenyeberang = true;
}