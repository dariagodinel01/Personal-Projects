from pyspark.sql import SparkSession
from pyspark.sql.functions import (col, count, sum, avg, countDistinct, 
                                   lag, when, lit, corr,  max as spark_max)
from pyspark.sql.window import Window

def main():
    # Setup and configuration
    spark = SparkSession.builder \
        .appName("GoogleClusterAnalysis") \
        .config("spark.executor.memory", "4g") \
        .getOrCreate()
    
    spark.sparkContext.setLogLevel("ERROR")
    MACHINE_EVENTS_PATH = "machine_events/part-00000-of-00001.csv.gz"
    JOB_EVENTS_PATH = "job_events/part-*.csv.gz"   
    TASK_EVENTS_PATH = "task_events/part-*.csv.gz" 
    TASK_USAGE_PATH = "task_usage/part-*.csv.gz"  

    print("Loading Dataframes...")

    # Map clumns to table heads form Schema
    machines_df = spark.read.csv(MACHINE_EVENTS_PATH, inferSchema=True) \
        .select(col("_c0").alias("time"), 
                col("_c1").alias("machine_id"), 
                col("_c2").alias("event_type"), 
                col("_c4").alias("CPUs"))
    tasks_df = spark.read.csv(TASK_EVENTS_PATH, inferSchema=True) \
        .select(col("_c0").alias("time"),
                col("_c2").alias("job_id"),
                col("_c3").alias("task_index"),
                col("_c4").alias("machine_id"),
                col("_c5").alias("event_type"),
                col("_c7").alias("scheduling_class"),
                col("_c9").alias("cpu_request"))
    usage_df = spark.read.csv(TASK_USAGE_PATH, inferSchema=True) \
        .select(col("_c2").alias("job_id"),
                col("_c3").alias("task_index"),
                col("_c4").alias("machine_id"),
                col("_c5").alias("cpu_rate"))
    
    machines_df.cache()

    # Q1
    print("\n Q1: Machine distribution by CPU capacity")
    q1 = machines_df.select("machine_id", "CPUs").distinct() \
                    .groupBy("CPUs").count().orderBy("CPUs")
    q1.show()

   
    # Q2   
    print("\n Q2: Lost computational power due to maintenance")
    # Define window per machine, ordered by time
    windowSpec = Window.partitionBy("machine_id").orderBy("time")
    # Calculate next time for every event
    m_events_lag = machines_df.withColumn("next_time", lag("time", -1).over(windowSpec)) \
                              .withColumn("next_event", lag("event_type", -1).over(windowSpec))
    # Filter for REMOVE events (1) and calculate how long they lasted
    maintenance = m_events_lag.filter(col("event_type") == 1) \
                              .withColumn("duration", col("next_time") - col("time")) \
                              .fillna(0, subset=["duration"])
    # Power Lost = Duration * CPUs
    lost_power = maintenance.withColumn("power_lost", col("duration") * col("CPUs"))
    total_loss = lost_power.select(sum("power_lost")).collect()[0][0]

    # Calculate the total available power
    total_available_power = m_events_lag.withColumn("duration", col("next_time") - col("time")) \
                                        .withColumn("available_power", col("duration") * col("CPUs")) \
                                        .select(sum("available_power")).collect()[0][0]
    # Calculate the percentage of computational power lost
    percentage_loss = (total_loss / total_available_power) * 100
    print(f"Percentage of computational power lost: {percentage_loss:.2f}%")
    
    # Q3   
    print("\n Q3: Maintenance rate by CPU class")
    # Use lost_power from Q2
    q3 = lost_power.groupBy("CPUs") \
                   .agg(avg("duration").alias("avg_maintenance_duration")) \
                   .orderBy("CPUs")
    q3.show()

    # Q4   
    print("\n Q4: Tasks per scheduling class")
    # Use task events
    q4 = tasks_df.groupBy("scheduling_class").count().orderBy("scheduling_class")
    q4.show()

    # Q5   
    print("\n Q5: Percentage of tasks killed or evicted")
    # Event Types: 2=EVICT, 5=KILL
    total_events = tasks_df.count()
    bad_events = tasks_df.filter(col("event_type").isin(2, 5)).count()
    print(f"Percentage: {(bad_events/total_events)*100:.2f}%")
    
    # Q6   
    print("\n Q6: Eviction probability by scheduling class")
    # 1 if evicted, 0 otherwise
    evict_df = tasks_df.withColumn("is_evicted", when(col("event_type") == 2, 1).otherwise(0))
    q6 = evict_df.groupBy("scheduling_class").agg(avg("is_evicted").alias("prob_eviction")).orderBy("scheduling_class")
    q6.show()
  
    # Q7   
    print("\n Q7: Task locality (Distinct machines per job)")
    # Filter for SCHEDULE events (type 1)
    scheduled = tasks_df.filter(col("event_type") == 1)
    # Count distinct machines per job
    job_machines = scheduled.groupBy("job_id").agg(countDistinct("machine_id").alias("unique_machines"))
    # Show distribution of machine counts 
    q7 = job_machines.groupBy("unique_machines").count().orderBy("unique_machines")
    q7.show(5)

    # Q8   
    print("\n Q8: Correlation between CPU Request and CPU Usage")
    # Avg CPU rate per task
    avg_usage = usage_df.groupBy("job_id", "task_index").agg(avg("cpu_rate").alias("avg_cpu_used"))
    # Distinct CPU request per task
    requests = tasks_df.select("job_id", "task_index", "cpu_request").distinct()    
    # Join
    joined_q8 = requests.join(avg_usage, ["job_id", "task_index"])
    # Correlation
    corr_val = joined_q8.stat.corr("cpu_request", "avg_cpu_used")
    print(f"Correlation between CPU Requested and Used: {corr_val}")

    # Q9   
    print("\n Q9: Correlation between machine max usage and eviction count")
    # Max CPU usage per machine
    mach_peaks = usage_df.groupBy("machine_id").agg(spark_max("cpu_rate").alias("max_cpu"))
    # Count of EVICT events (type 2) per machine
    mach_evicts = tasks_df.filter(col("event_type") == 2) \
                          .groupBy("machine_id").count().withColumnRenamed("count", "evict_count")
    # Join and correlate
    q9_df = mach_peaks.join(mach_evicts, "machine_id").fillna(0)
    print(f"Correlation: {q9_df.stat.corr('max_cpu', 'evict_count')}")

    # Q10   
    print("\n Q10: How often are machines over-committed?")
    # Get machine capacity
    q1_df = machines_df.select("machine_id", "CPUs").distinct()
    # Join usage with capacity
    q10_joined = usage_df.join(q1_df, "machine_id")
    # Find overloaded machines
    overloaded = q10_joined.filter(col("cpu_rate") > col("CPUs"))
    # Count overloaded instances
    overloaded_count = overloaded.count()
    total_usage_records = usage_df.count()    
    print(f"Overloaded instances: {overloaded_count} out of {total_usage_records}")

    # Q11   
    print("\n Q11: Job Size Distribution")
    # Count size of each job
    job_sizes = tasks_df.groupBy("job_id").agg(countDistinct("task_index").alias("num_tasks"))
    # Group by the size and count how many jobs of each size exist
    size_distribution = job_sizes.groupBy("num_tasks").count().orderBy("num_tasks")
    size_distribution.show(15)

    # Q12   
    print("\n Q12: Job locality vs. Kill probability")
   
    # Find how many distinct machines did each job touch
    job_spread = tasks_df.filter(col("event_type") == 1) \
                         .groupBy("job_id") \
                         .agg(countDistinct("machine_id").alias("machine_count"))
    # Check if the job has ANY event_type == 5 (KILL). (1 if the job had kills, 0 otherwise)
    job_kills = tasks_df.groupBy("job_id") \
                        .agg(spark_max(when(col("event_type") == 5, 1).otherwise(0)).alias("was_killed"))

    # Join Spread + Fate
    risk_analysis = job_spread.join(job_kills, "job_id", "left").fillna(0)

    # Compare single machine and multi-machine"
    result = risk_analysis.withColumn("is_distributed", col("machine_count") > 1) \
                          .groupBy("is_distributed") \
                          .agg(avg("was_killed").alias("probability_of_kill"), 
                               count("job_id").alias("total_jobs")) \
                          .orderBy("is_distributed")
    result.show()
    
    
    spark.stop()

if __name__ == "__main__":
    main()