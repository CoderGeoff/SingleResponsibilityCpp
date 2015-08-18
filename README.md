# SingleResponsibilityCpp
An exercise to underline the SRP

Here you will see the following classes

In WordCounter:
| Class | Description |
| DirectoryLexicalAnalyzer | This class provides lexical information on all the files in a directory. It counts the numbers of words it encouters, finds the length of the longest word and provides frequency data on word usage. |
| AnalyzedInputStream | This class has the tests that describe the contract for DirectoryLexicalAnalyzer |

In WordCounterTests:
| DirectoryLexicalAnalyzerTests | This class has the tests that describe the contract for DirectoryLexicalAnalyzer |
| TemporaryDirectory | A class that creates a temporary directory |
| TemporaryFile | A class that creates a temporary file |

DirectoryLexicalAnalyzer is an existing class. It is known to work reliably and it has tests against it to validate its behavior. 

## Task 1 
Read DirectoryLexicalAnalyzerTests and DirectoryLexicalAnalyzer. Comment on things that could be improved in the implementation of DirectoryLexicalAnalyzer and in the tests.

## Task 2
There is a new requirement for a input stream that reads words from the console (or conceivably some other stream) and analyzes them. Like DirectoryLexicalAnalyzer it must report on word count, the length of the longest word and word frequency. Since it has to create the same information, the wish is to reuse DirectoryLexicalAnalyzer in AnalyzedInputStream.

Your job is to make this happen. As you go, note separate what is making the job hard. 
