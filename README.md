

# bioinf
Izrada projekta u sklopu kolegija "Bioinformatika 1"

## Zadatak

*(1) The Logarithmic Dynamic Cuckoo Filter* (Zhang et al. 2021) (MDL)

- Zhang et al. The Logarithmic Dynamic Cuckoo Filter 
	doi: 10.1109/ICDE51399.2021.00087
	
- Chen et al. 2017. The dynamic cuckoo filter; https://ieeexplore.ieee.org/abstract/document/8117563
- Fan et al. 2013. Cuckoo Filter: Better Than Bloom;
https://www.cs.cmu.edu/~binfan/papers/login_cuckoofilter.pdf
- Fan et al. 2014. Cuckoo Filter: Practically Better Than Bloom;
http://www.cs.cmu.edu/%7Ebinfan/papers/conext14_cuckoofilter.pdf
- tražiti slučajne podnizove (k-mere uz različite k, npr. k = 10, 20, 50, 100, 200) u E. coli genomu
- napraviti vlastiti LDCF te usporediti s originalnom [implementacijom](https://github.com/CGCL-codes/LDCF)

Nastavnica: izv. prof. dr. sc. Mirjana Domazet-Lošo 
E-mail: mirjana.domazet@fer.hr

## Upute za izradu programa
- implementacija: C/C++
- svaka funkcija i klasa moraju biti komentirani
- dobro pisan kod ne treba pretjerane komentare. Ako se implementiraju poznati algoritmi dovoljno je
    samo navesti koji se algoritam implementira. Ako je neki komad koda nerazumljiv, onda se u
    komentaru prije njega treba jasno objasniti što će se raditi.
- treba naznačiti tko je napisao koji dio koda
- imena varijabli i komentari su na engleskom
- projekt treba raditi na linux OS - instalirati kao dual boot ili virtualni stroj npr. [VirtualBox](https://www.virtualbox.org/)
- sve dodatne vanjske knjižnice moraju biti uključene u izvorni kod
- instalacija i pokretanje iz naredbenoga retka
- svi parametri se unose jedino prilikom pokretanja programa u naredbenom retku ili iz konfiguracijske
datoteke
- izlaz programa mora biti u datoteku, a ukoliko se radi o poravnanju koristiti [MAF format](
http://genome.ucsc.edu/FAQ/FAQformat.html#format5)

Pročitati više u docs/"Upute za izradu projekta na predmetu Bioinformatika 1, 2022./2023.pdf"

## Upute za instalaciju i izvođenje
Potrebna je instalacija OpenSSL (više o OpenSSL-u: https://www.openssl.org).

```txt
sudo apt-get install openssl
sudo apt-get install libssl-dev
```

Pokretanje na Linuxu (terminal):
- Putem terminala doći u `src` datoteku
- Kompajlirati pokretanjem `g++ -o LDCF.out main.cpp cuckooFilter.cpp hashingFuncs.cpp LDCF.cpp countKmers.cpp -lssl -lcrypto` naredbe
- Pokrenuti `./LDCF.out [buckets] [entries] [fingerprint_size] [k-mere_size] [genome]`
        - "buckets", "entries", "fingerprint_size" i "k-mere_size" su traženi argumenti tipa 'int', a "genome" je put do izvornog filea je string
        - Npr. `./LDCF.out 10000 100 256 50 ecoli_genome.txt`
