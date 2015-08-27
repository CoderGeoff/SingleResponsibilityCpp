# SingleResponsibilityCpp
An exercise to underline the Single Responsibility Principle, using C++ and Visual Studio.
Based on Visual Studio 2013.

## Getting started

1. Clone the repository 
2. Open Visual Studio
3. Open the solution file, SingleResponsibility.sln, in the root directory of the repository
4. Build the project in Debug
5. Run the tests, Debug/WordCounterTests.exe 
6. Have a look at the code:

You will find:

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

DirectoryLexicalAnalyzer is an existing class and has (largely) been developed using TDD. It is known to work reliably and it has tests against it to validate its behavior. 

## Task 1 
Read DirectoryLexicalAnalyzerTests and DirectoryLexicalAnalyzer. Make a note of areas of the code that could be improved in the implementation of DirectoryLexicalAnalyzer *and in the tests*.
For each area you note, jot down what is wrong with it as well as the improvement that could be made.

## Task 2
There is a new requirement for a input stream, AnalyzedInputStream, that reads words from an input stream (perhaps an Html stream) and analyzes them. 
Similar to DirectoryLexicalAnalyzer it must report on word count and the length of the longest word. Since it has to create the same information, the 
wish is to reuse DirectoryLexicalAnalyzer in AnalyzedInputStream.

Your job is to implement AnalyzedInputStream. As you go, note separate what is making the job hard. There is the start of an implementation to help you.

## Task 3
It transpired during testing that the input stream analyzed by AnalyzedInputStream are multi-lingual and can quickly carry millions of different words. The memory consumed by the 
word frequency dictionary, m_Frequency, is causing performance problems, which you must now solve. Remember that AnalyzedInputStream doesn't need to count word frequencies: think about
how to do this and how the Single Responsibility Principle could help. 

## Task 4
There is now a requirement for AnalyzedInputStream to provide interim results of its analysis while the stream is being read as well as once the stream has terminated. Implement this.
