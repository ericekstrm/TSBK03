#version 400 core

in vec2 out_tex_coords;

uniform sampler2D main_pass;
uniform sampler2D god_ray_pass;
uniform vec2 sun_pos;

const float exposure = 0.1f;
const float decay = 0.96815;
const float density  = 0.926;
const float weight  = 0.587;
const int NUM_SAMPLES = 100;

out vec4 out_color;

void main()
{

    vec2 delta_tex_coord = vec2(out_tex_coords - sun_pos);
    vec2 tex_coord = out_tex_coords;
    delta_tex_coord *= 1.0 / float(NUM_SAMPLES) * density;
    float illumination_decay = 1.0;
    vec4 godray_color = vec4(0,0,0,0);

    for(int i = 0; i < NUM_SAMPLES; i++)
	{
		tex_coord -= delta_tex_coord;
		vec4 s = texture(god_ray_pass, tex_coord);
		s *= illumination_decay * weight;
		godray_color += s;
		illumination_decay *= decay;
	}

    out_color = texture(main_pass, out_tex_coords) + godray_color * exposure;

    //https://developer.nvidia.com/gpugems/gpugems3/part-ii-light-and-shadows/chapter-13-volumetric-light-scattering-post-process
    
    /*float4 main(float2 texCoord : TEXCOORD0) : COLOR0 {   
        // Calculate vector from pixel to light source in screen space.    
        half2 deltaTexCoord = (texCoord - ScreenLightPos.xy);   
        // Divide by number of samples and scale by control factor.   
        deltaTexCoord *= 1.0f / NUM_SAMPLES * Density;   
        // Store initial sample.   
        half3 color = tex2D(frameSampler, texCoord);   
        // Set up illumination decay factor.   
        half illuminationDecay = 1.0f;   
        // Evaluate summation from Equation 3 NUM_SAMPLES iterations.    
        for (int i = 0; i < NUM_SAMPLES; i++)   
        {     
            // Step sample location along ray.     
            texCoord -= deltaTexCoord;     
            // Retrieve sample at new location.    
            half3 sample = tex2D(frameSampler, texCoord);     
            // Apply sample attenuation scale/decay factors.     
            sample *= illuminationDecay * Weight;     
            // Accumulate combined color.     
            color += sample;     
            // Update exponential decay factor.     
            illuminationDecay *= Decay;  
        }   
        // Output final color with a further scale control factor.    
        return float4( color * Exposure, 1); 
    }*/
}
