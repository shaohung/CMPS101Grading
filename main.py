from Student import Student
import sys

def getStudents(path):
	with open("StudentRoster") as f:
		content = f.readlines()
		# you may also want to remove whitespace characters like `\n` at the end of each line
		students = [Student(x.strip(), path) for x in content]
		return students

def main():
	students = getStudents(sys.argv[1:][0])
	for student in students:
		student.grade()
	#now enter grade

if __name__ == "__main__":
	main()
