require "fileutils"

def compile out, flags, *paths
	sh "gcc -o #{out} #{flags} -lSDL -Iinclude #{paths.join " "}"
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
	debug "work/pmove", "test/pmove.c", "src/movement.c", "src/sdl.c"
	sh "work/pmove"
end
