import pygame

# starting pygame
pygame.init()

# display width and height
display_width = 800
display_height = 600

# the window and the title, putting a clock for now
gameDisplay = pygame.display.set_mode((display_width,display_height))
pygame.display.set_caption('Save the DE ball!')
clock = pygame.time.Clock()

# choosing two basic colors for now  
black = (0,0,0)
white = (255,255,255)
backgroundColor = (70, 130, 180)
   
# paddle function creates the paddle
def paddle(x , y, velocity):
  
   paddleImg = pygame.image.load('rect.jpg')
   paddleImg = pygame.transform.scale(paddleImg, (80, 20))
   if x  + velocity <= display_width + 80 and x - velocity>= 0:
      gameDisplay.blit(paddleImg, (x + velocity,y))
      pygame.display.update()
   else:
      gameDisplay.blit(paddleImg, (x,y))
      pygame.display.update()



def main():
   x =  (display_width * 0.45)
   y = (display_height * 0.8)
   crashed = False
   x_change = 0
   velocity = 0
   while not crashed:
      for event in pygame.event.get():
         if event.type == pygame.QUIT:
            crashed = True
         
      key_list = pygame.key.get_pressed()
      if key_list[pygame.K_LEFT]:
         x_change += -10
      if key_list[pygame.K_RIGHT]:
         x_change += 10
      gameDisplay.fill(backgroundColor)
      paddle(x, y, x_change)

        
      pygame.display.update()
      clock.tick(60)

   pygame.quit()
   quit()
main()