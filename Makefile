#!/usr/bin/make -f

all: pdf

clean:
	rubber --pdf --clean principal.tex
	make -C ejemplos $@

pdf:
	rubber --pdf principal.tex

ejemplos:
	make -C ejemplos

PHONY: all pdf
