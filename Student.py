import shutil, errno, subprocess, os
from Test import Test
from timeout import TimeoutError
from pathlib import Path

class Student:
	def __init__ (self, name, path):
		self.name = name
		self.score = 0
		self.points = 0
		self.report = ""
		self.path = path
		self.tests = None

	def copy_dir(self, src, dst):
		try:
			shutil.copytree(src, dst)
		except OSError as exc: # python >2.5
			if exc.errno == errno.ENOTDIR:
				shutil.copy(src, dst)
			else: raise

	def prepare(self):
		#copy student files to temp
		src = os.path.join(self.path, self.name)
		dst = os.path.join(os.getcwd(), 'temp')
		self.copy_dir(src, dst)
		self.copy_dir(os.path.join(os.getcwd(), 'Test'), os.path.join(dst, "Test"))
		with open("testlist") as f:
			content = f.readlines()
			# you may also want to remove whitespace characters like `\n` at the end of each line
			self.tests = [Test(x.strip(), os.path.join(dst, "Test")) for x in content]

	def remove(self):
		#delete temp folder
		shutil.rmtree(os.path.join(os.getcwd(), 'temp'))

	def compile(self):
		try :
			testResults = subprocess.check_output("make", cwd=os.path.join(os.getcwd(), 'temp'), shell=True)
			return True
		except subprocess.CalledProcessError as error :
			return False

	def grade(self):
		self.prepare()
		compiled = self.compile()

		for test in self.tests:
			self.points+=test.points

		if(compiled):
			#run all tests
			for test in self.tests:
				try:
					test.runTest()
				except TimeoutError as error:
					test.report+="timeout\n"

				self.score+=test.score
				#print("name: "+str(test.name))
				#print("score: " +str(test.score))
				#print("report: " + test.report)
			pass
		self.generateReport(compiled)
		self.remove()

	def generateReport(self, compiled):
		self.report += ("Total score: " + str(self.score) + "/" + str(self.points) + "\n")
		if(not compiled):
			self.report += "Could not compile code\n"
		else:
			self.report += ("\n-------------\n")
			for test in self.tests:
				self.report += ("name: " + str(test.name) + "\n")
				self.report += ("description: " + str(test.description) + "\n")
				self.report += ("url: " + str(test.url) + "\n")
				self.report += ("score: " + str(test.score) +"/" +str(test.points) + "\n")
				self.report += ("report: " +test.report + "\n")
				self.report += ("test output:\n")
				p = os.path.join(os.path.join(os.getcwd(), 'temp'), "Test")
				my_file = Path((p + "/" + "%s.out")%(test.name))
				if my_file.is_file():
					with open((p + "/" + "%s.out")%(test.name), 'r') as content_file:
						self.report+= content_file.read()
	 			self.report += ("\n-------------\n")

