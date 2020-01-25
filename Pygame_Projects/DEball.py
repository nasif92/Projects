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
def paddle(velocity):
   x =  (display_width * 0.45)
   y = (display_height * 0.8)

   paddleImg = pygame.image.load('rect.jpg')
   paddle_width = 20
   paddle_length = 80

   # scaling it down for window
   paddleImg = pygame.transform.scale(paddleImg, (paddle_length, paddle_width))
   if x + velocity < 0:
      gameDisplay.blit(paddleImg, (0,y))
   elif x + velocity > display_width - paddle_length:
      gameDisplay.blit(paddleImg, ( display_width - paddle_length , y))
   #if x + velocity < display_width - paddle_length and x + velocity> 0:
   else:
      gameDisplay.blit(paddleImg, (x + velocity,y))
      pygame.display.update()

def ball(game_over):
   x =  (int)(display_width /2)
   y = (int)(display_height /2)

   move = [ 10, -10]
   while not game_over:
      if x  <= 0:
         pygame.draw.circle(gameDisplay ,white, (x + move[0] , y ), 12)
      elif x  >= display_width:
         pygame.draw.circle(gameDisplay ,white, (x + move[1] , y ), 12)
      elif y <= 0:
         pygame.draw.circle(gameDisplay ,white, (x  , y + move[0]), 12)
      elif y >= 0 :
         pygame.draw.circle(gameDisplay ,white, (x  , y + move[1]), 12)


class Ball:
   def __init__(self,surface, color, pos, radius, speed):
      self.surface = surface
      self.color = color
      self.pos = pos
      self.radius = radius
      self.speed = speed

   def draw(self):
      pygame.draw.circle(self.surface, self.color,self.pos,self.radius)

   def bounce(self):
      # self.velocity[0] = -self.velocity[0]
      # self.velocity[1] = randint(-8,8)
      pass
   def move(self):
      size = [display_width,display_height]
      for coord in range(0,2):
         self.pos[coord] += self.speed
         if self.pos[coord] < self.radius:
            self.speed = -self.speed
         if self.pos[coord] + self.radius > size[coord]:
            self.speed = -self.speed
      


def main():
  
   crashed = False
   x_change = 0
   game_over = False

   
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
      paddle(x_change)

      # the DE ball 
      DEBall = Ball(gameDisplay,white, [round(display_width/2),round(display_height/2)],8 , 2)
      DEBall.draw()

      DEBall.move()


      pygame.display.update()
      clock.tick(60)

   pygame.quit()
   quit()
main()