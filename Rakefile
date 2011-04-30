require "fileutils"

ENGINE = ["src/player.c", "src/screen.c",
	"src/level.c", "src/timetrack.c",
	"src/control.c", "src/zone.c",
	"src/input.c", "src/sprite.c"]

def compile out, flags, *paths
	sh "g++ -o #{out} #{flags} `pkg-config --cflags --libs gobject-2.0` -lSDL -Iinclude #{ENGINE.join " "} #{paths.join " "}"
end

def debug out, *paths
	compile out, "-g", *paths
end

file "work" do
	FileUtils.mkdir "work"
end

desc "Clean tree"
task :clean do
	FileUtils.rm_r "work"
end

desc "Test player movement"
task :pmove => [:clean, "work"] do
	debug "work/pmove", "test/pmove.c"
	sh "work/pmove"
end
