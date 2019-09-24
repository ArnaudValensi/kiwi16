print("[LUA] Hello World")

t=0
function draw_bg()
 t=t+0.02

 for i=0,1000 do
  local x,y=math.random(0, 127),math.random(0, 127)
  local c=math.floor((x/16+y/32+t)%6+11)
  setpixel(x,y,c)
 end
end

function update()
  draw_bg()
end
