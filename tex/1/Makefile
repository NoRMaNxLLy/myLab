.PHONY: clean build

clean:
	rm *.idx *.log *.mst *.out *.xwm

veryclean:
	rm *.pdf *.aux *.toc

build: sample.md
	pandoc --template template.tex \
		-t latex \
		--pdf-engine xelatex \
		-o sample.tex \
		sample.md
