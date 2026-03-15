import random
import csv
import speech_recognition as sr
import pyttsx3
import schedule
import time
import json
from datetime import datetime

rec = sr.Recognizer()

class Factor(object):
    def _init_(self, id, name, status, time):
        self.id = id
        self.name = name
        self.status = status
        self.time = time

    def show(self):
        print("id: " + str(self.id) + " name: " + self.name + " status: " + self.status + " time: " + self.time)


class Person(Factor):
    def _init_(self, habit, location, id, name, status, time):
        super()._init_(id, name, status, time)
        self.habit = habit
        self.location = location
        self.bp = 0
        self.therm = 0
        self.gm = 0
        self.bracelet = 0
        self.pulse = 0
        self.oxi = 0

    def move(self):
        self.location = str(input("Enter location: "))

    def getIn(self):
        self.location = "Home"

    def getOut(self):
        self.location = "Outside"

    def use(self):
        print("The allowed devices are: blood pressure monitor, thermometer, glucose monitor, fitness bracelet "
              "pulse meter, oximeter")
        device = str(input("Enter device in use: "))
        if device == "blood pressure monitor":
            self.bp = 1
            self.bp_measure = random.randint(90,190)
        if device == "thermometer":
            self.therm = 1
            self.therm_measure = random.uniform(35, 39)
        if device == "glucose monitor":
            self.gm = 1
            self.gm_measure = random.randint(60, 180)
        if device == "fitness bracelet":
            self.bracelet = 1
            self.steps_measure = random.randint(0, 20000)
            self.sleep_measure = random.randint(0, 15)
        if device == "pulse meter":
            self.pulse = 1
            self.pulse_measure = random.randint(45,200)
        if device == "oximeter":
            self.oxi = 1
            self.oxi_measure = random.randint(0, 100)


class HomeAppliance(Factor):
    def _init_(self, location, effectLevel, id, name, status, time):
        super()._init_(id, name, status, time)
        self.location = location
        self.effectLevel = effectLevel

    def setStatus(self):
        print("Status can be Active or Inactive")
        self.status = str(input("Enter status: "))


class Environment(Factor):
    def _init_(self, temperature, humidity, illumination, noiseLevel, id, name, status, time):
        super()._init_(id, name, status, time)
        self.temperature = temperature
        self.humidity = humidity
        self.illumination = illumination
        self.noiseLevel = noiseLevel

    def getEnvironmentalInfo(self):
        print("Id: "+str(self.id)+" Name: "+str(self.name)+" Temperature: "+str(self.temperature)+" humidity: "+str(self.humidity)+" illumination: "+str(self.illumination)+" noise level: "+str(self.noiseLevel))


class Internal(Environment):
    def _init_(self, size, temperature, humidity, illumination, noiseLevel, id, name, status, time):
        super()._init_(temperature, humidity, illumination, noiseLevel, id, name, status, time)
        self.size = size

    def getEnvironmentFromApplianceEffect(self):
        print("Id: "+str(self.id)+" Name: "+str(self.name)+" Temperature: "+str(self.temperature)+" humidity: "+str(self.humidity)+" illumination: "+str(self.illumination)+" noise level: "+str(self.noiseLevel)+" size: "+str(self.size))


class Weather(Environment):
    def _init_(self, level,temperature, humidity, illumination, noiseLevel, id, name, status, time):
        super()._init_(temperature, humidity, illumination, noiseLevel, id, name, status, time)
        self.level = level

    def setEffect(self):
        print("The level should be between 0 and 100")
        self.level = int(input("Enter the level: "))



class VirtualSpace(object):
    def _init_(self, size, location, factors):
        self.size = size
        self.location = location
        self.factors = factors

    def show(self):
        print("Size: "+str(self.size)+" Location: "+str(self.location))
        for factor in self.factors:
            print(factor.name)

    def getEvent(self, res):
        res.dbConnection.read()
        events = res.getCases()
        print("For person with id: " + str(res.person.id))
        if len(events) == 0:
            print("All good, no events")
        else:
            print(events)
        res.dbConnection.close()

class Reasoning(object):
    def _init_(self, dbConnection, refSmartHome, environment, person):
        self.dbConnection = dbConnection
        self.refSmartHome = refSmartHome
        self.environment = environment
        self.person = person



    def getCases(self):
        e = []
        e = self.doReasoning()
        return e

    def doReasoning(self):
        events = []
        index = 0
        case2 = self.caseMatching()
        events.clear()
        while index < len(case2):
            event = self.dbConnection.rows[int(case2[index] / 10)][0] + ": " + self.dbConnection.header[int(case2[index] % 10)]
            events.append(event)
            del event
            index +=1
        case2.clear()
        return events

    def caseMatching(self):
        case = []
        case.clear()
        index = 0
        for row in self.dbConnection.rows:
            if person.bp == 1 and row[0] == "Hypertension":
                person.bp_measure = random.randint(90, 190)
                if person.bp_measure > float(row[4]):
                    case.append(index*10+4)
                elif person.bp_measure < float(row[1]):
                    case.append(index*10+1)
                elif person.bp_measure > float(row[3]):
                    case.append(index*10+3)
                else:
                    case.append(index*10+2)
            if person.therm == 1 and row[0] == "Fever":
                person.therm_measure = random.uniform(35, 39)
                if person.therm_measure > float(row[4]):
                    case.append(index*10+4)
                elif person.therm_measure < float(row[1]):
                    case.append(index*10+1)
                elif person.therm_measure > float(row[3]):
                    case.append(index*10+3)
                else:
                    case.append(index*10+2)
            if person.gm == 1 and row[0] == "Diabetes":
                person.gm_measure = random.randint(60, 180)
                if person.gm_measure > float(row[4]):
                    case.append(index*10+4)
                elif person.gm_measure < float(row[1]):
                    case.append(index*10+1)
                elif person.gm_measure > float(row[3]):
                    case.append(index*10+3)
                else:
                    case.append(index*10+2)
            if person.bracelet == 1:
                if row[0] == "Sedentariness":
                    person.steps_measure = random.randint(0, 20000)
                    if person.steps_measure > float(row[4]):
                        case.append(index*10+4)
                    elif person.steps_measure < float(row[1]):
                        case.append(index*10+1)
                    elif person.steps_measure > float(row[3]):
                        case.append(index*10+3)
                    else:
                        case.append(index*10+2)
                if row[0] == "Sleep quality":
                    person.sleep_measure = random.randint(0, 15)
                    if person.sleep_measure > float(row[4]):
                        case.append(index*10+4)
                    elif person.sleep_measure < float(row[1]):
                        case.append(index*10+1)
                    elif person.sleep_measure > float(row[3]):
                        case.append(index*10+3)
                    else:
                        case.append(index*10+2)

            if person.pulse == 1 and row[0] == "Tachycardia":
                person.pulse_measure = random.randint(45, 200)
                if person.pulse_measure > float(row[4]):
                    case.append(index*10+4)
                elif person.pulse_measure < float(row[1]):
                    case.append(index*10+1)
                elif person.pulse_measure > float(row[3]):
                    case.append(index*10+3)
                else:
                    case.append(index*10+2)

            if person.oxi == 1 and row[0] == "Hypoxemia":
                person.oxi_measure = random.randint(0, 100)
                if person.oxi_measure > float(row[2]):
                    case.append(index*10+2)
                elif person.oxi_measure < float(row[4]):
                    case.append(index*10+4)
                else:
                    case.append(index*10+1)
            if row[0] == "Stress":
                environment.noiseLevel = random.randint(40, 150)
                if environment.noiseLevel > float(row[4]):
                    case.append(index*10+4)
                elif environment.noiseLevel < float(row[1]):
                    case.append(index*10+1)
                elif environment.noiseLevel > float(row[3]):
                    case.append(index*10+3)
                else:
                    case.append(index*10+2)
            if row[0] == "Asthm":
                environment.humidity = random.randint(10, 80)
                if environment.humidity > float(row[4]):
                    case.append(index*10+4)
                elif environment.humidity < float(row[1]):
                    case.append(index*10+1)
                elif environment.humidity > float(row[3]):
                    case.append(index*10+3)
                else:
                    case.append(index*10+2)
            if row[0] == "Light_Disconfort":
                environment.illumination = random.randint(70, 180)
                if environment.illumination > float(row[4]):
                    case.append(index*10+4)
                elif environment.illumination < float(row[1]):
                    case.append(index*10+1)
                elif environment.illumination > float(row[3]):
                    case.append(index*10+3)
                else:
                    case.append(index*10+2)
                return case
            index += 1

    def getEnvironmentalInfo(self):
        print("Id: "+str(self.environment.id)+" Name: "+str(self.environment.name)+" Temperature: "+str(self.environment.temperature)+" humidity: "+str(self.environment.humidity)+" illumination: "+str(self.environment.illumination)+" noise level: "+str(self.environment.noiseLevel))


class DBConnection(object):
    def _init_(self, connectionString):
        self.connectionString = connectionString
        self.header = []
        self.rows = []

    def read(self):
        self.header.clear()
        self.rows.clear()
        self.file = open(self.connectionString)
        csvreader = csv.reader(self.file)
        self.header = next(csvreader)
        for row in csvreader:
            self.rows.append(row)

    def write(self, events):
        self.file = open(self.connectionString, 'a',  newline='')
        writer = csv.writer(self.file)
        writer.writerow(events)

    def close(self):
        self.file.close()


def SpeakText(command):
    engine = pyttsx3.init()
    engine.say(command)
    engine.runAndWait()


def daily(res, db):
    res.dbConnection.read()
    events = res.caseMatching()
    string = []
    emg, war, nor, bnor = 0, 0, 0, 0
    string.append(str(datetime.now()))
    for event in events:
        if int(event) % 10 == 1:
            bnor += 1
        elif int(event) % 10 == 2:
            nor +=1
        elif int(event) % 10 == 3:
            war +=1
        else:
            emg +=1
    string.append(emg)
    string.append(war)
    string.append(nor)
    string.append(bnor)
    db.write(string)
    res.dbConnection.close()
    db.close()
    events.clear()
    string.clear()


def weekly(db1, db2):
    db1.read()
    a = len(db1.rows)
    events = []
    for i in range(7):
        events.append(db1.rows[a-i-1])
    string = []
    emg, war, nor, bnor = 0, 0, 0, 0
    string.append(str(datetime.now()))
    for event in events:
        emg += int(event[1])
        war += int(event[2])
        nor += int(event[3])
        bnor += int(event[4])
    string.append(emg)
    string.append(war)
    string.append(nor)
    string.append(bnor)
    db2.write(string)
    db1.close()
    db2.close()
    events.clear()
    string.clear()


def monthly(db1, db2):
    db1.read()
    events = []
    a = len(db1.rows)
    for i in range(4):
        events.append(db1.rows[a-i-1])
    string = []
    emg, war, nor, bnor = 0, 0, 0, 0
    string.append(str(datetime.now()))
    for event in events:
        emg += int(event[1])
        war += int(event[2])
        nor += int(event[3])
        bnor += int(event[4])
    string.append(emg)
    string.append(war)
    string.append(nor)
    string.append(bnor)
    db2.write(string)
    db1.close()
    db2.close()
    events.clear()
    string.clear()



def yearly(db1, db2):
    db1.read()
    events = []
    a = len(db1.rows)
    for i in range(12):
        events.append(db1.rows[a-i-1])
    string = []
    emg, war, nor, bnor = 0, 0, 0, 0
    string.append(str(datetime.now()))
    for event in events:
       emg += int(event[1])
       war += int(event[2])
       nor += int(event[3])
       bnor += int(event[4])
    string.append(emg)
    string.append(war)
    string.append(nor)
    string.append(bnor)
    db2.write(string)
    db1.close()
    db2.close()
    events.clear()
    string.clear()

def decision(ok):
    if ok == "Y":
        try:
            with sr.Microphone() as source2:
                rec.adjust_for_ambient_noise(source2, duration=0.2)
                audio3 = rec.listen(source2)
                choice = rec.recognize_google(audio3)
                choice = choice.lower()
                print("Did you say " + choice)
                SpeakText(choice)
        except sr.RequestError as e:
            print("Could not request results; {0}".format(e))
        except sr.UnknownValueError:
            print("unknown error occured")
    else:
        choice = input("Your action: ")
    return choice

def analytics(j):
    f = open(j)
    data = json.load(f)
    total = 0
    i = 1
    while i < len(data["dataSource"]['data']):
        total += data["dataSource"]['data'][i][1]
        i += 1
    print("Mean emergencies: ", total/(len(data["dataSource"]['data'])-1))
    total = 0
    i = 1
    while i < len(data["dataSource"]['data']):
        total += data["dataSource"]['data'][i][2]
        i += 1
    print("Mean warnings: ", total/(len(data["dataSource"]['data'])-1))
    total = 0
    i = 1
    while i < len(data["dataSource"]['data']):
        total += data["dataSource"]['data'][i][3]
        i += 1
    print("Mean normal: ", total/(len(data["dataSource"]['data'])-1))
    total = 0
    i = 1
    while i < len(data["dataSource"]['data']):
        total += data["dataSource"]['data'][i][4]
        i += 1
    print("Mean below normal: ", total/(len(data["dataSource"]['data'])-1))
    f.close()

if _name_ == "_main_":
    db = DBConnection("diseases.csv")
    persons = [Person("smoking", "Home", 1, "Person 1", "Active", "23 days"), Person("drinking", "Bedroom", 2, "Person 2", "Active", "26 days")]
    environments = [Environment(random.uniform(10, 30), random.randint(10,80), random.randint(70, 180), random.randint(40, 150), 4, "Home", "Active", "200 days"),
                    Internal(20, random.uniform(10, 30), random.randint(10,80), random.randint(70, 180), random.randint(40, 150), 5, "Living Room", "Active","200 days"),
                    Internal(5, random.uniform(10, 30), random.randint(10,80), random.randint(70, 180), random.randint(40, 150), 6, "Bathroom", "Active","200 days"),
                    Internal(15, random.uniform(10, 30), random.randint(10,80), random.randint(70, 180), random.randint(40, 150), 7, "Bedroom", "Active","200 days"),
                    Internal(10, random.uniform(10, 30), random.randint(10,80), random.randint(70, 180), random.randint(40, 150), 8, "Kitchen", "Active","200 days")]
    appliances = [HomeAppliance("Kitchen", random.randint(0,100), 9, "Stove", "Inactive", "2 days"), HomeAppliance("Living Room", random.randint(0,100), 10, "TV", "Active", "2 hours"),
                  HomeAppliance("Bathroom", random.randint(0,100), 11, "Washing machine", "Inactive", "6 days"), HomeAppliance("Bedroom", random.randint(0,100), 12, "Alarm Clock", "Inactive", "18 hours")]
    weather = [Weather(random.randint(0,100), random.uniform(10, 30), random.randint(10,80), random.randint(70, 180), random.randint(40, 150), 13, "Rain", "Active", "2 hours"),
               Weather(random.randint(0,100), random.uniform(10, 30), random.randint(10,80), random.randint(70, 180), random.randint(40, 150), 14, "Sunny", "Inactive", "12 hours"),
               Weather(random.randint(0,100), random.uniform(10, 30), random.randint(10,80), random.randint(70, 180), random.randint(40, 150), 15, "Snow", "Inactive", "100 days")]
    factors = [Factor(3, "factor", "Inactive", "100 days")]
    for person in persons:
        factors.append(person)
    for environment in environments:
        factors.append(environment)
    for appliance in appliances:
        factors.append(appliance)
    for w in weather:
        factors.append(w)
    vSpace = VirtualSpace(50, "Bucharest", factors)
    print("Do you want to activate voice recognition? Y/N")
    choice3 = input("Your action: ")
    while True:
        print("Options: Info Factor->1; Action Person->2; Change HomeAppliance->3")
        print("Info Environment->4; Info Internal->5; Change Weather->6; Info Virtual Space->7")
        print("Exit->any key")
        choice = decision(choice3)
        if choice == "1":
            for factor in factors:
                factor.show()
        elif choice == "2":
            while True:
                print("Move->1; Get in->2; Get out->3; Use device->4; Go back to main menu->any key")
                choice2 = decision(choice3)
                if choice2 == "1":
                    p = int(input("Person id:"))
                    index = 0
                    for person in persons:
                        if p != person.id:
                            index += 1
                        else:
                            break
                    persons[index].move()
                elif choice2 == "2":
                    p = int(input("Person id:"))
                    index = 0
                    for person in persons:
                        if p != person.id:
                            index += 1
                        else:
                            break
                    persons[index].getIn()
                elif choice2 == "3":
                    p = int(input("Person id:"))
                    index = 0
                    for person in persons:
                        if p != person.id:
                            index += 1
                        else:
                            break
                    persons[index].getOut()
                elif choice2 == "4":
                    p = int(input("Person id:"))
                    index = 0
                    for person in persons:
                        if p != person.id:
                            index += 1
                        else:
                            break
                    persons[index].use()
                else:
                    break
        elif choice == "3":
            p = int(input("Appliance id:"))
            index = 0
            for appliance in appliances:
                if p != appliance.id:
                    index += 1
                else:
                    break
            appliances[index].setStatus()
        elif choice == "4":
            for environment in environments:
                environment.getEnvironmentalInfo()
        elif choice == "5":
            for internal in environments:
                if type(internal) is Internal:
                    internal.getEnvironmentFromApplianceEffect()
        elif choice == "6":
            p = int(input("Weather id:"))
            index = 0
            for w in weather:
                if p != w.id:
                    index += 1
                else:
                    break
            weather[index].setEffect()
        elif choice == "7":
            while True:
                print("Show->1; Get events->2; Go back to main menu->any key ")
                choice2 = decision(choice3)
                if choice2 == "1":
                    vSpace.show()
                elif choice2 == "2":
                    p = int(input("Person id:"))
                    index = 0
                    for person in persons:
                        if p != person.id:
                            index += 1
                        else:
                            break
                    if persons[index].location != "Outside":
                        for environment in environments:
                            if environment.name == persons[index].location:
                                e = environment
                                break
                        r = Reasoning(db, "reference", e, persons[index])
                        vSpace.getEvent(r)
                    else:
                        print("Sorry we have no info! :(")
                else:
                    break
        else:
            break
    print("Per day:")
    analytics('report_daily.json')
    print("Per week:")
    analytics('report_weekly.json')
    print("Per month:")
    analytics('report_monthly.json')
    print("Per year:")
    analytics('report_yearly.json')
    for environment in environments:
        if environment.name == persons[0].location:
            e = environment
            break
    r = Reasoning(db, "reference", e, persons[0])
    db2 = DBConnection("daily.csv")
    db3 = DBConnection("weekly.csv")
    db4 = DBConnection("monthly.csv")
    db5 = DBConnection("yearly.csv")
    schedule.every(5).seconds.do(daily, r, db2)
    schedule.every(36).seconds.do(weekly, db2, db3)
    schedule.every(142).seconds.do(monthly, db3, db4)
    schedule.every(1710).seconds.do(yearly, db4, db5)

    while True:
        schedule.run_pending()
        time.sleep(1)