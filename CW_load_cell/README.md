# Program do Kalibracji Klucza Morse'a

Ten program służy do kalibracji klucza Morse'a poprzez pomiar odczytów z czujnika i przeliczenie ich na factor_dit i factor_dash.  

## Uruchomienie

1. Podłącz klucz do portu szeregowego.
2. Uruchom program calibracja – na ekranie pojawi się aktualna wartość odczytana z belki.

## Instrukcja kalibracji

### 1. Kalibracja "dash" (długa kreska)

1. Ustaw klucz poprzecznie, łopatka z kreskami skierowana do góry.
2. Odczytaj wartość czujnika i zapisz jako `waga 0`.
3. Połóż na łopatkę monetę o znanej wadze i odczytaj wartość – zapisz jako `waga X gramów`.
4. Powtarzaj, dokładając kolejne monety i zapisując kolejne odczyty.
5. Calkowita waga oklo 50 gr

**Przykład dla monety 1-funtowej (waga 8.75 g):**

| Waga [g] | Odczyt |
|-----------|--------|
| 0         | 90000  |
| 8.75      | 150000 |
| 17.5      | 200000 |

### 2. Obliczenie współczynnika dash

Dla każdej linii obliczamy wartość:


linie z 1 monetą: (150000 - 90000) / 8.75              =6857

linie z 2 monetami: (200000 - 90000) / (8.75 * 2)      =6285

Z wyliczonych wartosci przyjmujemy srednia wartosc ktora zapisujemy w factor_dash


### 3. To samo powtarzamy dla dit

Klucz obrocic o 180 stopni lopatki kropek do gory
