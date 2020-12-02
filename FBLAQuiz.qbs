import qbs

Product {
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
            "mainwindow.h",
            "question.h",
            "questioncontainer.h",
            "questionset.h",
            "quizwindow.h",
        ]
    }
    Group {
        name: "src"
        prefix: "src/"
        files: [
            "main.cpp",
            "mainwindow.cpp",
            "question.cpp",
            "questioncontainer.cpp",
            "questionset.cpp",
            "quizwindow.cpp",
        ]
    }
}
