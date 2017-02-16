import os, subprocess
class Test :
	def __init__ (self, testname, path):
		self.path = path
		self.commands = [command.rstrip() for command in open(os.path.join(path, testname))]
		self.points = self.commands[0]
		self.description = self.commands[1]
		self.name = testname
		self.report = ""
		self.score = 0
		del self.commands[0]
		del self.commands[0]

	def runTest(self):
		for command in self.commands:
			try :
				testResults = subprocess.check_output(command, shell=True, cwd=self.path)
			except subprocess.CalledProcessError as error :
				self.report +="Test Failure for command "  + command + "\n"
				return
			#Perform diff comparison of expected output and actual output
		try:
			subprocess.check_call(("diff -w -b %s.out %s.expected") % (self.name, self.name), shell=True, cwd = self.path)
		except :
			self.report +=("Test failed due to comparison failure.") + "\n"
		
		#valgrind --leak-check=full ./Test_Constructor >> Test_Constructor.out
		with open(os.path.join(self.path, "memoryLeak")) as f:
			content = f.readlines()
			for line in content:
				if 'no leaks are possible' in line:
					self.score = self.points
					return
		self.report +=("Test failed due to memory leak.") + "\n"
