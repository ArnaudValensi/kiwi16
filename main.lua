print("[LUA] Hello World")

t=0
function draw_bg()
 t=t+0.02

 for i=0,4000 do
  local x,y=math.random(0, 256),math.random(0, 143)
  local c=math.floor((x/16+y/32+t)%3+10)
  setpixel(x,y,c)
 end
end

function update()
  draw_bg()
end
