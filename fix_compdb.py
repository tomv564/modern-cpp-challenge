
if __name__ == "__main__":
	with open("build/compile_commands.json") as f:
		for line in f:
			print line