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

- Linie z 1 monetą: `(150000 - 90000) / 8,75 = 6 857`  
- Linie z 2 monetami: `(200000 - 90000) / (8,75 × 2) = 6 285`  

Z wyliczonych wartości przyjmujemy średnią, którą zapisujemy w `factor_dash`.

---

### 3. Kalibracja "dit" (kropka)

1. Obróć klucz o 180° tak, aby łopatki kropek były skierowane do góry.  
2. Powtórz procedurę opisaną w sekcji 1–2, aby wyliczyć i zapisać `factor_dit`.


# Morse Key Calibration Program

This program is used to calibrate a Morse key by measuring sensor readings and converting them into `factor_dit` and `factor_dash`.

---

## Getting Started

1. Connect the Morse key to the serial port.  
2. Run the `calibracja` program – the current value from the key's lever will be displayed on the screen.

---

## Calibration Instructions

### 1. Dash ("–") Calibration

1. Position the key horizontally with the dash paddle facing up.  
2. Read the sensor value and record it as `weight 0`.  
3. Place a coin of known weight on the paddle and record the sensor reading as `weight X g`.  
4. Repeat by adding more coins and recording each reading.  
5. Total weight should be approximately 50 g.

**Example for a 1-pound coin (weight 8.75 g):**

| Weight [g] | Sensor Reading |
|------------|----------------|
| 0          | 90,000         |
| 8.75       | 150,000        |
| 17.5       | 200,000        |

---

### 2. Calculating the Dash Factor

For each measurement, calculate the value:

- Single-coin line: `(150000 - 90000) / 8.75 = 6,857`  
- Two-coin line: `(200000 - 90000) / (8.75 × 2) = 6,285`  

The average of the calculated values is assigned to `factor_dash`.

---

### 3. Dit ("·") Calibration

1. Rotate the key 180° so that the dot paddle faces up.  
2. Repeat the procedure from sections 1–2 to calculate and save `factor_dit`.
