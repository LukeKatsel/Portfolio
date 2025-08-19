from drawingpanel import *


def main():

 
    panel4 = DrawingPanel(1000, 1000)

    panel4.set_background(Color.LIGHT_GRAY);
    g = panel4

    g.set_fill_color(Color.BLACK);
    g.draw_rect(10, 30, 100, 50, fill = "black");

    g.set_color(Color.RED);
    g.draw_oval(20, 70, 20, 20, fill = "red");
    g.draw_oval(80, 70, 20, 20, fill = "red");

    g.set_color(Color.CYAN);
    g.draw_rect(80, 40, 30, 20, fill = "cyan");
    
    
    
    #panel4.draw_oval(250, 200, 500, 500, fill = "red")
    
    panel4.draw_rect(250, 425, -150, 40, fill = "black")
    
    panel4.draw_rect(750, 425, 150, 40, fill = "black")
    
    panel4.draw_rect(563, 660, 40, 250, fill = "black")

    panel4.draw_rect(397, 660, 40, 250, fill = "black") 
    
    panel4.draw_oval(250, 200, 500, 500, fill = "red")

    panel4.draw_oval(395, 20, 200, 200, fill = "green")       
    
    panel4.draw_arc(445, 90, 95, 100, 180, 180, color="white")
    
    panel4.draw_oval(455, 100, 10, 10, fill = "red")
    
    panel4.draw_oval(520, 100, 10, 10, fill = "red")

    panel4.draw_rect(85, 425, -5, -20, fill = "orange") 
    
    panel4.draw_rect(42, 457, 25, 5, fill = "orange") 
    
    panel4.draw_rect(42, 447, 25, 5, fill = "orange") 
    
    panel4.draw_rect(42, 437, 25, 5, fill = "orange") 
    
    panel4.draw_rect(42, 427, 25, 5, fill = "orange") 
    
    panel4.draw_oval(110, 470, -50, -50, fill = "blue") 
    
    panel4.draw_rect(900, 425, -5, -20, fill = "orange")     
        
    panel4.draw_rect(910, 457, 25, 5, fill = "orange") 
    
    panel4.draw_rect(910, 447, 25, 5, fill = "orange") 
    
    panel4.draw_rect(910, 437, 25, 5, fill = "orange") 
    
    panel4.draw_rect(910, 427, 25, 5, fill = "orange")     
    
    panel4.draw_oval(920, 470, -50, -50, fill = "blue")       
    
    
    
    
    panel4.set_fill_color("yellow")
    
    panel4.fill_oval(100, 100, 200, 200)
    
    panel4.set_fill_color("black")
    
    panel4.fill_oval(150, 150, 30, 30)
    panel4.fill_oval(220, 150, 30, 30)
    
    panel4.set_fill_color("white")   
    
    panel4.fill_arc(150, 200, 100, 100, 0, -180)    
    
    
    
    
if __name__ == "__main__":
    main()
