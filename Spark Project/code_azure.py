import os
import subprocess
import sys

from pyspark.sql import SparkSession
from pyspark.sql.functions import col, avg, count, max, desc
import pyspark.sql.functions as F

def main():
    # Setup and configuration
    spark = SparkSession.builder \
        .appName("StudentAzureAnalysis") \
        .config("spark.driver.memory", "4g") \
        .getOrCreate()

    spark.sparkContext.setLogLevel("ERROR")
    current_folder = os.getcwd()
    tar_file = os.path.join(current_folder, "azurefunctions-dataset2019.tar.xz")
    extract_folder = os.path.join(current_folder, "extracted_data")
    print(f"Working in: {current_folder}")

    if not os.path.exists(extract_folder):
        print("Extracting data... please wait...")
        os.makedirs(extract_folder, exist_ok=True)
        subprocess.check_call(["tar", "-xJf", tar_file, "-C", extract_folder])
        print("Extraction finished!")
    else:
        print("Data is already extracted.")

    # Load data into spark
    csv_path = f"file://{extract_folder}/invocations_per_function_md.anon.d01.csv"
    print(f"Reading CSV file: {csv_path}")
    df = spark.read.csv(csv_path, header=True, inferSchema=True)

    # Q1: How many functions are in this dataset?
    print("\n Q1: Total number of functions")
    total_functions = df.count()
    print(f"Count: {total_functions}")

    # Q2: What triggers these functions?
    print("\n Q2: Types of triggers")
    trigger_counts = df.groupBy("Trigger").count().orderBy(desc("count"))
    trigger_counts.show()

    # Q3: Calculate total invocations per function
    print("\n Q3: Calculating total invocations")
    # Get a list of all column names that are numbers
    all_columns = df.columns
    minute_columns = []
    for c in all_columns:
        if c.isdigit():
            minute_columns.append(c)
    # We add a temporary column for each batch sum
    temp_batch_columns = []
    df_calculated = df
    
    batch_size = 100
    # Loop through the columns in chunks of 100
    for i in range(0, len(minute_columns), batch_size):
        current_batch = minute_columns[i : i + batch_size]
        # '1' + '2' + ... + '100'
        formula = " + ".join([f"`{c}`" for c in current_batch])
        
        # Add a temporary column with the sum
        batch_name = f"batch_sum_{i}"
        df_calculated = df_calculated.withColumn(batch_name, F.expr(formula))
        temp_batch_columns.append(batch_name)

    # Sum up all the temporary batch columns to get the total
    final_formula = " + ".join([f"`{c}`" for c in temp_batch_columns])
    df_calculated = df_calculated.withColumn("total_invocations", F.expr(final_formula))
    
    print("Top 10 busiest functions:")
    df_calculated.select("HashFunction", "Trigger", "total_invocations") \
                 .orderBy(desc("total_invocations")) \
                 .show(10)

    # Q4: Which trigger type creates the most load?
    print("\n Q4: Average load by trigger type")
    df_calculated.groupBy("Trigger") \
        .agg(avg("total_invocations").alias("avg_calls"), 
             max("total_invocations").alias("max_calls")) \
        .orderBy(desc("avg_calls")) \
        .show()

    # Q7: Which Application is the biggest?
    print("\n Q7: Top applications (Apps with most invocations)")
    df_calculated.groupBy("HashApp") \
        .agg(count("HashFunction").alias("function_count"),
             F.sum("total_invocations").alias("app_total_calls")) \
        .orderBy(desc("app_total_calls")) \
        .show(5)

    spark.stop()

if __name__ == "__main__":
    main()
