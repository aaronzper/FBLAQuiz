import qbs

Product {
	name: "fbla_quiz"
	type: ["application"]
	Depends {
		name: "Qt"
		submodules: ["core", "gui", "printsupport"] // Add more here if needed
	}
	cpp.includePaths: "include/"
	cpp.cxxLanguageVersion: "c++17"
	files: [
		"example.fblaquiz"
	]
	Group {
		name: "include"
		prefix: "include/"
		files: [
			"*"
		]
	}
	Group {
		name: "src"
		prefix: "src/"
		files: [
			"*"
		]
	}
}
