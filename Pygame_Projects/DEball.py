import pygame
import random

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
def paddle(velocity):
   x =  (display_width * 0.45)
   y = (display_height * 0.8)

   paddleImg = pygame.image.load('rect.jpg')
   paddle_width = 20
   paddle_length = 80
   x_pos = 0
   y_pos = 0
   # scaling it down for window
   paddleImg = pygame.transform.scale(paddleImg, (paddle_length, paddle_width))
   if x + velocity < 0:
      gameDisplay.blit(paddleImg, (0,y))
      y_pos = y
   elif x + velocity > display_width - paddle_length:
      gameDisplay.blit(paddleImg, ( display_width - paddle_length , y))
      x_pos = display_width - paddle_length
      y_pos = y
   else:
      gameDisplay.blit(paddleImg, (x + velocity,y))
      pygame.display.update()
      x_pos = x + velocity
      y_pos = y
   return x_pos,y_pos




class Ball:
   def __init__(self,surface, color, radius, speed):
      self.surface = surface
      self.color = color
      self.pos = [round(display_width/2),round(display_height/2)]
      self.radius = radius
      self.speed = [speed, speed]

   def draw(self):
      pygame.draw.circle(self.surface, self.color,self.pos,self.radius)
   
   def bounce(self):
      self.speed[1] = -self.speed[1]
      self.speed[0] = random.randint(-8,8)
      
   def move(self):
      size = [display_width,display_height]
      for coord in range(0,2):
         self.pos[coord] += self.speed[coord]
         if self.pos[coord] < self.radius:
            self.speed[coord] = -self.speed[coord]
         if self.pos[coord] + self.radius > size[coord]:
            self.speed[coord] = -self.speed[coord]
   def positions(self):
      return self.pos
   
def bounce_the_ball(radius,ball_x, ball_y, paddle_x, paddle_y):
   if ball_y + radius <= paddle_y and ball_x + radius <= paddle_x:
      return True
   

def main():
  
   crashed = False
   x_change = 0
   game_over = False

   DEBall = Ball(gameDisplay,white, 8 , 2)

   # the main game
   while not crashed:
      for event in pygame.event.get():
         if event.type == pygame.QUIT:
            crashed = True
         
      # list of keys that's pressed
      key_list = pygame.key.get_pressed()

      # change in paddle when pressed
      if key_list[pygame.K_LEFT]:
         x_change += -10
      if key_list[pygame.K_RIGHT]:
         x_change += 10
      gameDisplay.fill(backgroundColor)
      paddle_x,paddle_y = paddle(x_change)
      

      # the DE ball being drawn and moved
      DEBall.draw()
      DEBall.move()

      ball_x, ball_y = DEBall.positions()
      if bounce_the_ball(8,ball_x,ball_y, paddle_x, paddle_y):
         DEBall.bounce()



      pygame.display.update()
      clock.tick(60)

   pygame.quit()
   quit()
main()