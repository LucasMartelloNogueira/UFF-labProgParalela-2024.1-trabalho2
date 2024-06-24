# Ambiente virtual Python

## criando ambiente virtual

    python -m venv .venv

## ativando o venv

    .venv\Scripts\activate

## baixando dependencias

    pip install -r requirements.txt


## adicionando novas dependencias

    pip freeze > requirements.txt

__

---
__



# Compilar e executar programas

## Naive (openmp_primos.c)

### Compilar
    gcc -o openmp_primos.exe openmp_primos.c -fopenmp

### Rodar
    openmp_primos.exe <n> <num_threads>
