# -*- coding: utf-8 -*-

from distutils.core import setup 
import py2exe 
 
setup(name="ProyectEvr", 
 version="1.0", 
 description="Programa para leer y guardar informacion del banco de pruebas evr", 
 author="Laboratorio CAF", 
 author_email="ign.gga@outlook.cl", 
 url="https://github.com/IgnGGA/cafProyect01.git", 
 license="Licencia de Software LIbre", 
 scripts=["reader.py"], 
 console=["reader.py"], 
 options={"py2exe": {"bundle_files": 1}}, 
 zipfile=None,
)