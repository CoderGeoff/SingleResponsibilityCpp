# SingleResponsibilityCpp
An exercise to underline the SRP

Here you will see the following classes

In WordCounter:

| Class | Description |
|-------|-------------|
| DirectoryLexicalAnalyzer | Provides lexical information on all the files in a directory. It counts the numbers of words it encouters, finds the length of the longest word and provides frequency data on word usage. |
| AnalyzedInputStream | The beginnings of an implemenation for a stream that analyzes its intput  |

In WordCounterTests:

| Class | Description |
|-------|-------------|
| DirectoryLexicalAnalyzerTests | The tests that describe the contract for DirectoryLexicalAnalyzer |
| TemporaryDirectory | A temporary directory |
| TemporaryFile | A temporary file |

DirectoryLexicalAnalyzer is an existing class. It is known to work reliably and it has tests against it to validate its behavior. 

## Task 1 
Read DirectoryLexicalAnalyzerTests and DirectoryLexicalAnalyzer. Comment on things that could be improved in the implementation of DirectoryLexicalAnalyzer and in the tests.

## Task 2
There is a new requirement for a input stream, AnalyzedInputStream, that reads words from the console (or conceivably some other stream) and analyzes them. Like DirectoryLexicalAnalyzer it must report on word count, the length of the longest word and word frequency. Since it has to create the same information, the wish is to reuse DirectoryLexicalAnalyzer in AnalyzedInputStream.

Your job is to implement AnalyzedInputStream. As you go, note separate what is making the job hard. There is the start of an implementation to help you.
