import shutil, errno, subprocess, os
from Test import Test

class Student:
	def __init__ (self, name, path):
		self.name = name
		self.score = 0
		self.report = None
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
		if(compiled):
			#run all tests
			for test in self.tests:
				test.runTest()
				print("name" + test.name)
				print("score" + str(test.score))
				print("report"+test.report)
			pass
		self.remove()
