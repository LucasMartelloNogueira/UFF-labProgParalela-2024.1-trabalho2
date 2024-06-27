import pandas as pd
import subprocess
import os
import time
from tqdm import tqdm


def create_file(filename: str) -> None:
    if os.path.exists(filename) is False:
        df = pd.DataFrame(columns=["program", "threads", "time", "n", "speed-up", "eficiencia"])
        df.to_csv(filename, index=False)


def run_file(input_filename: str, output_filename: str, n: int, num_threads: int) -> None:
    with open(output_filename, "a") as f:
        subprocess.call([input_filename, str(n), str(num_threads)], stdout=f)


def run_executions(input_filename: str, output_filename: str, threads_list: list[int], n_list: list[int]):

    for num_thread in threads_list:
        for n in n_list:
            run_file(input_filename, output_filename, n, num_thread)


def run_executions_v2(input_filename: str, output_filename: str, combinations):
    for n, num_threads in tqdm(combinations, total=len(combinations)):
        run_file(input_filename, output_filename, n, num_threads)


def read_data(filename):
    df = pd.read_csv(filename)
    print(df)


def calculate_metrics(filename: str):
    df = pd.read_csv(filename)

    nums = [10**6, 10**7, 10**8]
    threads = [2, 4, 8]

    for n in nums:
        df2 = df[df["n"] == n]
        # print(df2)
        t1 = df2.loc[df2["threads"] == 1, "time"].values[0]
        for t in threads:
            # print(f"{t1=}")
            tn = df2.loc[df2["threads"] == t, "time"].values[0]
            # print(f"{tn=}")
            speed_up = round(t1 / tn, 3)
            efficiency = round(speed_up / t, 2)
            
            df.loc[(df["n"] == n) & (df["threads"] == t), "speed-up"] = speed_up
            df.loc[(df["n"] == n) & (df["threads"] == t), "eficiencia"] = efficiency

    print(df)
    df.to_csv(filename, index=False)



def main():
    output_file = "data.csv"
    input_naive = "naive.exe"
    create_file(output_file)

    nums = [10**6, 10**7, 10**8]
    threads = [1, 2, 4, 8]
    combinations = [(n, thread) for n in nums for thread in threads]

    # run_executions(input_naive, output_file, threads, nums)
    # run_executions_v2(input_naive, output_file, combinations)

    # read_data(filename=output_file)
    # calculate_metrics(output_file)

    read_data(output_file)


if __name__ == "__main__":
    main()