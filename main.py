from Student import Student
import sys, os

def getStudents(path):
	with open("StudentRoster") as f:
		content = f.readlines()
		# you may also want to remove whitespace characters like `\n` at the end of each line
		students = [Student(x.strip(), path) for x in content]
		return students

def main():
	students = getStudents(sys.argv[1:][0])

	with open('gradereport', 'a') as f1:
		f1.write('Student ID, pa2 [100]\n')
		for student in students:
			print(student.name)
			student.grade()
			studentfolder = os.path.join(sys.argv[1:][0], student.name)
			studentreport = os.path.join(studentfolder, 'report.txt')
			with open(studentreport, 'w') as f:
				f.write(student.report)
			f1.write(student.name+","+str(student.score)+"\n")

	#with open('gradereport', 'w') as f:
		#f.write('Student ID, pa2 [100]\n')
		#for student in students:
			#f.write(student.name+","+str(student.score)+"\n")
	a = [0.0]*(len(students[0].tests))
	for j in range(0, len(a)):
		for i in range(0, len(students)):
			a[j]+=(students[i].tests[j].score)
		a[j]/=len(students)
		print(students[0].tests[j].name+ ":" + str(a[j])+"/"+str(students[0].tests[j].points))
	#[x for x in os.listdir('mossabc/moss-taps/data/Current/pa2/')]
	#now enter grade

if __name__ == "__main__":
	main()
