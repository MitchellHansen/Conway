uniform sampler2D frontBuffer;
uniform sampler2D backBuffer;
uniform vec4 alive_color;
uniform bool flipp;

void main() {

    vec4 self;

    if (flipp){
        self = texture2D(frontBuffer, gl_TexCoord[0].xy);
        
        int neighbors = 0;

        neighbors += texture2D(frontBuffer, gl_TexCoord[0].xy + (0, 1)) == alive_color ? 1 : 0;
        neighbors += texture2D(frontBuffer, gl_TexCoord[0].xy + (1, 0)) == alive_color ? 1 : 0;
        neighbors += texture2D(frontBuffer, gl_TexCoord[0].xy + (0,-1)) == alive_color ? 1 : 0;
        neighbors += texture2D(frontBuffer, gl_TexCoord[0].xy + (-1,0)) == alive_color ? 1 : 0;

        neighbors += texture2D(frontBuffer, gl_TexCoord[0].xy + (1, 1)) == alive_color ? 1 : 0;
        neighbors += texture2D(frontBuffer, gl_TexCoord[0].xy + (1,-1)) == alive_color ? 1 : 0;
        neighbors += texture2D(frontBuffer, gl_TexCoord[0].xy + (-1, 1)) == alive_color ? 1 : 0;
        neighbors += texture2D(frontBuffer, gl_TexCoord[0].xy + (-1,-1)) == alive_color ? 1 : 0;
        
       	if (neighbors == 3 || (neighbors == 2 && self == alive_color)) {
			self = alive_color;
		}
		else
			self.xyzw = (0.0, 0.0, 0.0, 0.0);

    } else {
        self = texture2D(backBuffer, gl_TexCoord[0].xy);
        
        int neighbors = 0;

        neighbors += texture2D(backBuffer, gl_TexCoord[0].xy + (0, 1)) == alive_color ? 1 : 0;
        neighbors += texture2D(backBuffer, gl_TexCoord[0].xy + (1, 0)) == alive_color ? 1 : 0;
        neighbors += texture2D(backBuffer, gl_TexCoord[0].xy + (0,-1)) == alive_color ? 1 : 0;
        neighbors += texture2D(backBuffer, gl_TexCoord[0].xy + (-1,0)) == alive_color ? 1 : 0;
        neighbors += texture2D(backBuffer, gl_TexCoord[0].xy + (1, 1)) == alive_color ? 1 : 0;
        neighbors += texture2D(backBuffer, gl_TexCoord[0].xy + (1,-1)) == alive_color ? 1 : 0;
        neighbors += texture2D(backBuffer, gl_TexCoord[0].xy + (-1, 1)) == alive_color ? 1 : 0;
        neighbors += texture2D(backBuffer, gl_TexCoord[0].xy + (-1,-1)) == alive_color ? 1 : 0;
        
       	if (neighbors == 3 || (neighbors == 2 && self == alive_color)) {
			self = alive_color;
		}
		else
			self.xyzw = (0.0, 0.0, 0.0, 0.0);
    }

    gl_FragColor = gl_Color * self;
}


