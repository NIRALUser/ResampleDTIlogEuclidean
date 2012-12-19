

NAME = ArticleExample

BIBTEXDATABSENAME = InsightJournal


all: ps pdf dvi
#all: pdf dvi 


ps: ${NAME}.ps


pdf: ${NAME}.pdf


dvi: ${NAME}.dvi


bbl: ${NAME}.bbl



${NAME}.ps: ${NAME}.dvi
	dvips -o ${NAME}.ps ${NAME}.dvi


${NAME}.pdf: ${NAME}.ps
	ps2pdf ${NAME}.ps

#${NAME}.pdf: ${NAME}.dvi
#	pdflatex ${NAME}.tex

${NAME}.bbl: ${BIBTEXDATABSENAME}.bib ${NAME}.aux
	bibtex ${NAME}

${NAME}.dvi: ${NAME}.tex  ${BIBTEXDATABSENAME}.bib
	latex ${NAME}.tex
	bibtex ${NAME}
	latex ${NAME}.tex
	latex ${NAME}.tex

${NAME}.aux: ${NAME}.tex  ${BIBTEXDATABSENAME}.bib
	latex ${NAME}.tex

clean:
	rm ${NAME}.dvi ${NAME}.pdf ${NAME}.aux ${NAME}.log ${NAME}.bbl ${NAME}.blg ${NAME}.toc ${NAME}.out  ${NAME}.brf  ${NAME}.ps

