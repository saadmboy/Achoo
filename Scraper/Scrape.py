import urllib2
import string
import json
import time
#import lxml #http://lxml.de/ Used to parse the html
from lxml import html

#@author Saad Kothawala

DISEASE_LIST_LINK_BASE = "http://www.mayoclinic.org/diseases-conditions/index?letter="
MAIN_LINK = "http://www.mayoclinic.org"
FILE_NAME = "diseases.json"

print ("--------------Starting Mayo Clinic Scraper--------------")

data = {}
startTime = time.time()
data['lastUpdated'] = startTime


diseasesAdded = []

count = 0
for letter in string.ascii_lowercase:#Go through all the alphabet
	page = urllib2.urlopen(DISEASE_LIST_LINK_BASE + letter).read() #get the html
	tree = html.fromstring(page) #make the html easier to use
	links = tree.xpath('//*[@id="index"]/ol/li/a') #Get all diseases in the listing

	for l in links:
		diseaseName = l.text
		if diseaseName[0].lower() == letter and diseaseName not in diseasesAdded:#to avoid duplicates
			count += 1
			print count, ": ", diseaseName
			diseaseLink = MAIN_LINK + l.attrib['href'].replace('definition', 'symptoms')
			
			diseasePage = urllib2.urlopen(diseaseLink).read()
			diseaseTree = html.fromstring(diseasePage)
			symptoms = diseaseTree.xpath('//*[@id="main-content"]/ul[1]/li')
			symptomsJSON = []
			for symptom in symptoms:
				if not "Tweet" in symptom.text_content() and not "Share" in symptom.text_content():
					symptomsJSON.append(symptom.text_content().replace("\r\n", ""))

			data[diseaseName] = symptomsJSON
			diseasesAdded.append(diseaseName)

obj = open(FILE_NAME, 'wb')
obj.write(json.dumps(data))
obj.close
			

print ("--------------Done Running Mayo Clinic Scraper--------------\n")
print "Elements Added: ", count
print "Run Time: ", time.time() - startTime, " seconds\n"