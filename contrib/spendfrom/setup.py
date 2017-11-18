from distutils.core import setup
setup(name='utbspendfrom',
      version='1.0',
      description='Command-line utility for alisinabit "coin control"',
      author='Gavin Andresen',
      author_email='gavin@alisinabitfoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
