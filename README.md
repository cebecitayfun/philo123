# 42 Philosophers (Dine Out)

Turkish & English guide for compiling and running the 42 Philosophers project.

---

## 🇹🇷 Türkçe Açıklama

Bu proje, işletim sistemlerindeki **Thread (İş Parçacığı)** oluşturma, **Mutex (Kilit)** yönetimi ve **Data Race (Veri Yarışı)** ile **Deadlock (Kilitlenme)** problemlerini çözmeyi hedefleyen klasik "Yemek Yiyen Filozoflar" problemidir.

### Proje Yapısı
Tüm kaynak dosyaları, 42 teslimat standartlarına uygun olarak `philo/` dizini altındadır:
* `setup.c`: Simülasyon, filozof ve çatal ilklendirmeleri.
* `engine.c`: Gözlemci ve filozof thread döngüleri.
* `routines.c`: Yeme, uyuma ve düşünme eylemleri.
* `helpers.c`: Atoi, zaman damgası ve hassas uyku yardımcıları.

### Derleme ve Çalıştırma
Proje dizinine (`philo/`) girin ve derleyin:
```bash
cd philo
make
```

Çalıştırma formatı:
```bash
./philo [filozof_sayisi] [olum_suresi] [yeme_suresi] [uyku_suresi] [istege_bagli_ogun_sayisi]
```
Örnek:
```bash
./philo 5 800 200 200
```

---

## 🇬🇧 English Description

This project is an implementation of Dijkstra's classic "Dining Philosophers" problem. It focuses on thread creation, mutex synchronization, and avoiding concurrency issues like deadlocks and data races.

### Project Structure
All source files are located inside the `philo/` directory to meet 42 evaluation rules:
* `setup.c`: Initialization of the simulation, philosophers, and forks.
* `engine.c`: Main philosopher and supervisor thread routines.
* `routines.c`: Dining, sleeping, and thinking behavior.
* `helpers.c`: Timestamping, custom sleep, and basic C helpers.

### Compilation and Execution
Navigate into the `philo/` directory and compile:
```bash
cd philo
make
```

Run command format:
```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```
Example:
```bash
./philo 5 800 200 200
```
