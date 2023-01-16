# MazeGenerator-Java
You can get auto-generated maze. (written by Java)  
  
If this Readme has some grammertical mistake, sorry. I'm still learning English.  
Also, the code still have Japanese javadoc comment. I will change it someday :)  
  
I am reffering to this web-site : Algoful https://algoful.com/Archive/Algorithm/MazeExtend  
This github's program is written in Java based on the site's program(written in C#), but the algorithm and code's structure is not exactly the same.  
  
I already confirmed that a maze of 501 x 501 size can generated within 1 second on my laptop.
  
## Remaining problem
I may refactor it someday........?  
  
The most important problem is that this maze tend to be easy.  
I think that this is caused by the limit of size of java.util.Stack.   
Because this code use java.util.Stack to avoid extend wall will connect now-extending-wall, large-size-maze(ex. 2001x2001) may occer StackOverflowError.  
To prevent this situation, I decide the max size of Stack at 7.  
However, because of this limitation, the shortest path tend to be easy route...  
